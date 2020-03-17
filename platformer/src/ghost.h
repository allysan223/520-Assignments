#ifndef __GHOST_AGENT__H
#define __GHOST_AGENT__H 

#include "enviro.h"

using namespace enviro;

class GhostController : public Process, public AgentInterface {

    public:
    GhostController() : Process(), AgentInterface(), vx(20) {}

    void init() {
        counter = 0;
        prevent_rotation();
        // notice_collisions_with("Bumper", [&](Event &e) {
        //     if ( counter == 0 ) {
        //       vx = -vx;
        //       counter = 10;
        //     }
        // });    
        std::cout << "ghost start \n";
        decorate(R"(<g>
            <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
            <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");

        std::cout << "ghost init done \n";
    }

    void start() {}

    void update() {
        double fx = -30*(velocity().x-vx);
        omni_apply_force(fx,0);
        if ( counter > 0 ) {
            counter--;
        }
        if ((x() < -128 || x() > 128) && counter == 0){
            vx = -vx;
            counter = 10;
        }
    }

    void stop() {}

    double vx;
    int counter;

};

class Ghost : public Agent {
    public:
    Ghost(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GhostController c;
};

DECLARE_INTERFACE(Ghost)

#endif