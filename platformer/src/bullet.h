#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        notice_collisions_with("Ghost", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
        });  
        std::cout << "bullet init done \n";            
    }
    void start() {}
    void update() {
        if (  abs(vx()) < 2 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif