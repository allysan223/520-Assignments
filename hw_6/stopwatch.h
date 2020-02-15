#ifndef __STOPWATCH_H
#define __STOPWATCH_H

#include <iostream>
#include "elma/elma.h"

typedef std::chrono::duration<double,std::nano> nanoseconds_type;
typedef std::chrono::duration<double,std::milli> milliseconds_type;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
typedef std::chrono::duration<double,std::ratio<60,1>> minutes_type;

using namespace std;
using namespace std::chrono;



class Stopwatch
{
private:
    high_resolution_clock::time_point t_start;
    high_resolution_clock::time_point t_stop;
    duration<double> stopwatch_span;


public:
    Stopwatch(/* args */);
    ~Stopwatch();
    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double
};

Stopwatch::Stopwatch(/* args */)
{
    reset();
}

Stopwatch::~Stopwatch()
{
}

// starts the timer
void Stopwatch::start(){
    t_start = high_resolution_clock::now();
}

// stops time
void Stopwatch::stop(){
    t_stop = high_resolution_clock::now();
}


void Stopwatch::reset(){
    stopwatch_span = nanoseconds_type::zero();
}

// get time in minutes
double Stopwatch::get_minutes(){
    stopwatch_span = stopwatch_span + duration_cast<duration<double>>(t_stop - t_start);
    auto elapsed_mins = minutes_type(stopwatch_span);
    std::cout << "stopwatch:  " << elapsed_mins.count() << " minutes. \n";

    return elapsed_mins.count();
}

// get time in secs
double Stopwatch::get_seconds(){
    stopwatch_span = stopwatch_span + duration_cast<duration<double>>(t_stop - t_start);
    std::cout << "stopwatch:  " << stopwatch_span.count() << " seconds. \n";

    return stopwatch_span.count();
}

// get time in milli
double Stopwatch::get_milliseconds(){
    stopwatch_span = stopwatch_span + duration_cast<duration<double>>(t_stop - t_start);
    auto elapsed_milli = milliseconds_type(stopwatch_span);
    std::cout << "stopwatch:  " << elapsed_milli.count() << " milliseconds. \n";

    return elapsed_milli.count();
}

// get time in nano
double Stopwatch::get_nanoseconds(){
    stopwatch_span = stopwatch_span + duration_cast<duration<double>>(t_stop - t_start);
    auto elapsed_nano = nanoseconds_type(stopwatch_span);
    std::cout << "stopwatch:  " << elapsed_nano.count() << " nanoseconds. \n";

    return elapsed_nano.count();
}

#endif