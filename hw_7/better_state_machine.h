#ifndef _ELMA_BETTER_STATE_MACHINE_H
#define _ELMA_BETTER_STATE_MACHINE_H

#include "elma/elma.h"
#include <iostream>
#include <json/json.h>
#include <list>


using nlohmann::json; 
using namespace std;

using namespace elma;

//! A finite state machine class

class BetterStateMachine : public StateMachine { 

    public:
    BetterStateMachine(string name) : StateMachine(name) {}

    //! This method should return a representation of a StateMachine as a json object
    json to_json() {
        json j;
        vector<Transition> transitions;
        int size = _transitions.size();
        vector <string> events, to, from, states;
        //gather wanted data
        for (int i = 0; i < size; i ++){
            events.push_back(_transitions[i].event_name());
            cout << i << ": " << events[i] << "\n";
            to.push_back(_transitions[i].to().name());
            states.push_back(_transitions[i].to().name());
            cout << i << ": " << to[i] << "\n";
            from.push_back(_transitions[i].from().name());
            states.push_back(_transitions[i].from().name());
            cout << i << ": " << from[i] << "\n";
            j["transitions"][i]["from"] = from[i];
            j["transitions"][i]["to"] = to[i];
            j["transitions"][i]["when"] = events[i];
        }
        j["name"] = name();
        //remove dups in states
        sort( states.begin(), states.end() );
        states.erase( unique( states.begin(), states.end() ), states.end() );
        j["states"] = states;
        //j["transitions"] = 

        return j;
    };

};



#endif
