#ifndef __BUMPER_AGENT__H
#define __BUMPER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BumperController : public Process, public AgentInterface {

    public:
    BumperController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("Player1", [&](Event &e) {
            remove_agent(id());
        });  
        notice_collisions_with("Player2", [&](Event &e) {
            remove_agent(id());
        });  
    }
    void start() {}
    void update() {}
    void stop() {}

};

class Bumper : public Agent {
    public:
    Bumper(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BumperController c;
};

DECLARE_INTERFACE(Bumper)

#endif