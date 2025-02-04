#include <exception>
#include "db.h"
#include <iostream>
#include <random>

using namespace std;

DB::DB() {
    _next_key =0;
    totalSize =0;
}


DB &DB::insert(const string name, double mass, double distance) {
    auto rows = where([name](DB::Row row) { return  NAME(row) == name; }); 
        if (rows.size() > 0 )
            throw runtime_error("Name already exists");

    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);

    totalSize++;

    return *this;

}

DB &DB::create_test_data(int n) {
    string name = "";
    double mass, distance;
    double massMin = 0.01;
    double massMax = 1000; 
    double distanceMin = 0.1;
    double distanceMax = 10000000;

    for ( int i = 0; i < n; i++){
        try{
            //generate name composed of random characters (lower case) *per TA
            int len = 15;
            char* name = (char*)malloc(sizeof(char) * len);
            gen_random(name, len);
            //name = "exoplanet" + to_string(_next_key);

            //generate random mass & distance
            mass = (massMax - massMin) * ( (double)rand() / (double)RAND_MAX ) + massMin;
            distance = (distanceMax - distanceMin) * ( (double)rand() / (double)RAND_MAX ) + distanceMin;
            insert(name, mass, distance);
            cout << name << ", mass: " << mass << ", distance: " << distance << "\n";
        } catch (const std::runtime_error& e) {
            // try again if try throws std::runtime_error (i.e: duplicate name)
            i--;
        }
        
    }
    return *this;
}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }
    totalSize--;
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

double DB::accumulate(function<double(const DB::Row)> f) const {
    double sum = 0;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        sum += f(row) ;
    }
    return sum;
}

int DB::size() const{
    return totalSize;
}

double DB::average_mass() const {
    double sum = accumulate([](DB::Row row) { return MASS(row); });
    return sum / (double)size();
}
double DB::average_distance() const{
    double sum = accumulate([](DB::Row row) { return DISTANCE(row); });
    return sum / (double)size();
}

void gen_random(char *s, const int len) {

    static const char rand_letter[] =
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = rand_letter[rand() % (sizeof(rand_letter) - 1)];
    }

    s[len] = 0;
}
