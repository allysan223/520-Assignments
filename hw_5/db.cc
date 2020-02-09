#include <exception>
#include "db.h"

using namespace std;

DB::DB() : _next_key(0) {}


DB &DB::insert(const string name, double mass, double distance) {
    auto rows = where([name](DB::Row row) { return  NAME(row) == name; }); 
        if (rows.size() > 0 )
            throw runtime_error("Name already exists");

    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }

    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

DB::Row DB::find_by_name(const string name) const {
    auto rows = where([name](DB::Row row) { return  NAME(row) == name; }); 

    if (rows.size() == 0 )
        throw runtime_error("Could not find row by name");

    return rows[0];

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

