#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"
#include <iostream>

using namespace elma;

class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};

class Wander : public State {
    public:
    Wander() : State("Wander") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "intruder detected" ) {
            emit(Event("Make Noise"));
        }
        if ( e.name() == "battery low" ) {
            emit(Event("Find Recharge Station"));
        }      
    }
};

class MakeNoise : public State {
    public:
    MakeNoise() : State("Make Noise") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "proximity warning" ) {
            emit(Event("Evade"));
        }
        if ( e.name() == "reset" ) {
            emit(Event("Wander"));
        }
    }
};

class Evade : public State {
    public:
    Evade() : State("Evade") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "reset" ) {
            emit(Event("Make Noise"));
        }
        if ( e.name() == "battery low" ) {
            emit(Event("Find Recharge Station"));
        }
    }
};

class FindRechargeStation : public State {
    public:
    FindRechargeStation() : State("Find Recharge Station") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "reset" ) {
            emit(Event("Make Noise"));
        }
        if ( e.name() == "battery low" ) {
            emit(Event("Find Recharge Station"));
        }
    }
};

class Recharge : public State {
    public:
    Recharge() : State("Recharge") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "battery full" ) {
            emit(Event("Wander"));
        }
    }
};

class Robot : public StateMachine {

    public:

    Robot(string name) : StateMachine() {
        set_initial(wander);
        add_transition("intruder detected", wander, make_noise);
        add_transition("reset", make_noise, wander);
        add_transition("proximity warning", make_noise, evade);
        add_transition("reset", evade, make_noise);
        add_transition("battery low", evade, find_recharge_station);
        add_transition("battery low", wander, find_recharge_station);
        add_transition("found recharge station", find_recharge_station, recharge);
        add_transition("battery full", recharge, wander);        
    }

    private:

    Wander wander;
    MakeNoise make_noise;
    Evade evade;
    FindRechargeStation find_recharge_station;
    Recharge recharge;      

};



#endif