#ifndef __DB_H
#define __DB_H

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <functional>

using namespace std;

#define KEY get<0>
#define NAME get<1>
#define MASS get<2>
#define DISTANCE get<3>

void gen_random(char *s, const int len);


class DB {

  public:

    
    typedef tuple<int,string,double,double> Row;

    DB();
    DB &insert(const string, double, double);
    DB &drop(int);
    DB &create_test_data(int n);

    Row find(int) const;
    Row find_by_name(const string) const;

    vector<Row> where(function<bool(const Row)> f) const;
    double accumulate(function<double(const Row)> f) const;
    int size() const;

    double average_mass() const;
    double average_distance() const;
    

  private:

    typedef tuple<string,double,double> Value;
    Row to_row(int,const Value) const;
    map<int,Value> _data;
    int _next_key;
    int totalSize;

};

#endif