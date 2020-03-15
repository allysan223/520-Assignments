#ifndef __GUY_AGENT__H
#define __GUY_AGENT__H 

#include "enviro.h"
#include <math.h>
#include <string>


using namespace enviro;

double min(double a, double b) {
    if ( a < b ) { 
        return a;
    } else {
        return b;
    }
}

class GuyController : public Process, public AgentInterface {

    public:
    GuyController() : Process(), AgentInterface(), LEFT(false), RIGHT(false), JUMP(false) {}

    double height() {
        return min(sensor_value(0), sensor_value(1));
    }

    double airborne() { 
        return height() > H_MIN;
    }

    void init() {
        //data for health bar
        for (int i = 0; i <= 200; i +=20){
            health_len.push_back(std::to_string(i)); 
        }
        Agent &health_bar = find_agent(3);
        health_bar.decorate(R"(<rect x=0 y=-10 width=200 height=20 fill="green" />)");
        
        label("P1", -8, -20 );
        prevent_rotation();
        watch("keydown", [&](Event& e) {
            std::string k = e.value()["key"];
            //shoot bullet in appropiate dirrection
            if ( k == "q" ) {
                if (prevState == "right"){
                  Agent& bullet = add_agent("Bullet", 
                                            x() + 17*cos(angle()), 
                                            y() + 17*sin(angle()), 
                                            angle(), 
                                            BULLET_STYLE);
                    bullet.apply_force(50,0);
                }
                if (prevState == "left") {
                    Agent& bullet = add_agent("Bullet", 
                                            x() - 17*cos(-angle()), 
                                            y() - 17*sin(-angle()), 
                                            -angle(), 
                                            BULLET_STYLE);
                    bullet.apply_force(-50,0);
                }
                
                  //firing = true;
            } else if ( k == "w" && ! airborne() ) {
                JUMP = true;
            } else if ( k == "a" ) {
                LEFT = true;
                prevState = "left";
            } else if ( k == "d" ) {
                RIGHT = true;
                prevState = "right";
            } 
        });
        watch("keyup", [&](Event& e) {
            std::string k = e.value()["key"];
            if ( k == "a" ) {
                LEFT = false;
            } else if ( k == "d" ) {
                RIGHT = false;
            }
        });     
        
        notice_collisions_with("Ghost", [&](Event &e) {
            teleport(0,135,0);
        });
            
       
    }
    void start() {}

    void update() {
        double fx;
        double fy = JUMP ? JUMP_F : 0;
        if ( !airborne() ) {
            if ( RIGHT ) {
                vx = VEL_X;
            } if ( LEFT ) {
                vx = -VEL_X;
            } else if ( !RIGHT && !LEFT ) {
                vx = 0;
            }
            fx = -K_X*(velocity().x-vx);
        } else {
            if ( RIGHT ) {
                vx = 0.1*VEL_X;
            } if ( LEFT ) {
                vx = -0.1*VEL_X;
            }            
            fx = 0;
            fx = -K_X*(velocity().x-vx);
        }
        omni_apply_force(fx,G+fy);
        JUMP = false;

        //decorations
        if (LEFT){
            decorate(R"(<g>
                <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
                </g>)");   
        } else if (RIGHT){
            decorate(R"(<g>
                <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");   
        } else {
            decorate(R"(<g>
                <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
                <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");    
        }
        
        notice_collisions_with("Bullet", [&](Event &e) {
            remove_agent(e.value()["id"]);
            Agent &health_bar = find_agent(3);
            decoration = "R\"(<rect x=0 y=-10 width=" + health_len[10-healthCounter] + " height=20 fill=\"green\" />)\"";
            //health_bar.set_style(ATTACKED_STYLE);
            health_bar.decorate(decoration);
            healthCounter++;
            if (healthCounter == 11)
                healthCounter = 0;
            }); 
    }

    void stop() {}

    
    int healthCounter;

    bool LEFT, RIGHT, JUMP;
    double vx;

    std::string prevState, decoration;
    vector<std::string> health_len;

    const double VEL_X = 25;
    const double JUMP_F = -2200;
    const double K_X = 15;
    const double G = 500; //600
    const double H_MIN = 1.0;
    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };
    const json ATTACKED_STYLE = { 
                   {"fill", "red"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };


};

class Player1 : public Agent {
    public:
    Player1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GuyController c;
};

DECLARE_INTERFACE(Player1)

#endif