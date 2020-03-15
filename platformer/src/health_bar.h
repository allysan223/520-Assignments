#ifndef __Health_AGENT__H
#define __Health_AGENT__H 

#include "enviro.h"

using namespace enviro;

class HealthController : public Process, public AgentInterface {

    public:
    HealthController() : Process(), AgentInterface() {}

    void init() {
        Agent &health_bar_p1 = find_agent(3);
        health_bar_p1.label("Player 1:", 0, -15 );
        Agent &health_bar_p2 = find_agent(4);
        health_bar_p2.label("Player 2:", 0, -15 );
    }
    void start() {}
    void update() {}
    void stop() {}

};

class Health : public Agent {
    public:
    Health(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    HealthController c;
};

DECLARE_INTERFACE(Health)

#endif