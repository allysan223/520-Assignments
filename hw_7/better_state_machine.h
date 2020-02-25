#ifndef _ELMA_BETTER_STATE_MACHINE_H
#define _ELMA_BETTER_STATE_MACHINE_H

#include "elma/elma.h"
#include <iostream>
#include <json/json.h>


using nlohmann::json; 
using namespace std;

using namespace elma;

//! A finite state machine class

class BetterStateMachine : public StateMachine { 

    public:
    BetterStateMachine(string name) : StateMachine() {}

    //! This method should return a representation of a StateMachine as a json object
    json to_json() const {
        json j;
        j["test"] = "test";
        j["name"] = name(); 
        return j;
    };

    // protected:
    // vector<Transition> _transitions;
    // State * _initial;
    // State * _current;
    // bool _propagate;

};



#endif
