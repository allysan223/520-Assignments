#ifndef __Health_AGENT__H
#define __Health_AGENT__H 

#include "enviro.h"

using namespace enviro;

class HealthController : public Process, public AgentInterface {

    public:
    HealthController() : Process(), AgentInterface() {}

    void init() {
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