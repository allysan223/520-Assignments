#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"
#include <iostream>

using namespace enviro;
using namespace std;

class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        watch("connection", [&](Event e) {
            if ( ! e.value()["client_id"].is_null() ) {
                std::cout << "Connection from " << e.value() << "\n";
                Agent& a = add_agent("Player1", 0, y, 0, {{"fill","gray"},{"stroke","black"}});
                a.set_client_id(e.value()["client_id"]);
                y += 50;
                cout << "Agent added \n";
            }
        });
        std::cout << "coordinator init done \n";
    }
    void start() {}
    void update() {
    }
    void stop() {}

    double y = -150;

};

class Coordinator : public Agent {
    public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif