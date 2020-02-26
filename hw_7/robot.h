#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"
#include <iostream>

using namespace elma;

//Class for defining modes (states)
class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    Mode() : State() {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};

class Robot : public StateMachine {

    public:

    Robot(string name) : StateMachine(name) {
        //initalize all states
        wander = Mode("Wander"); 
        make_noise =  Mode("Make Noise");
        evade =  Mode("Evade");
        find_recharge_station = Mode("Find Recharge Station");
        recharge = Mode("Recharge");

        //iniitalize all transistions
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
    Mode wander;
    Mode make_noise;
    Mode evade;
    Mode find_recharge_station;
    Mode recharge;    

};


#endif