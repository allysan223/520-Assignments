#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 
#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include <math.h>
#include "enviro.h"
using namespace std::chrono;

namespace {

    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "MOVING FORWARD.. "<< "\n";
        }
        void during() { 
            track_velocity(4,0);
            if ( sensor_value(0) < 10  && sensor_value(2) > 15) { //turn left 90
                std::cout << "FRONT SENSOR LESS THAN 10 "<< "\n";
                emit(Event("tick_nameL"));
            }
            if ( sensor_value(0) < 10  && sensor_value(1) > 15) { //turn left 90
                std::cout << "FRONT SENSOR LESS THAN 10 "<< "\n";
                emit(Event("tick_nameR"));
            }
      
        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class RotatingL : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "START TURNN LEFTTT: " << angle() << "\n";
            startAngle = angle();
            apply_force(-40, 0);
        } //{ rate = rand() % 2 == 0 ? 2 : -2; }
        void during() { 
            if ( sensor_value(0) > 100  ) {
                emit(Event(tick_name));
            }
            track_velocity(0,-0.1);
        }
        void exit(const Event& e) {}
        double rate, angleVal, startAngle;
        bool turningL, turningR;
        int stopLeft, stopRight;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class RotatingR : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "START TURNN LEFTTT: " << angle() << "\n";
            startAngle = angle();
            apply_force(-40, 0);
        } //{ rate = rand() % 2 == 0 ? 2 : -2; }
        void during() { 
            if ( sensor_value(0) > 100  ) {
                emit(Event(tick_name));
            }
            track_velocity(0,0.1);
        }
        void exit(const Event& e) {}
        double rate, angleVal, startAngle;
        bool turningL, turningR;
        int stopLeft, stopRight;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class Straighten : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "START STRAIGHTEN: " << angle() << "\n";
            //apply_force(-40, 0);
        } //{ rate = rand() % 2 == 0 ? 2 : -2; }
        void during() { 
            if(sensor_value(2)> sensor_value(1)){
                track_velocity(0,-0.1);
                std::cout << "START STRAIGHTEN LEFT " << "\n";
            } else {
                track_velocity(0,0.1);
                std::cout << "START STRAIGHTEN RIGHT " << "\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(4));
            emit(Event("tick_name_straight"));
        }
        void exit(const Event& e) {}
        double rate, angleVal, startVal;
        bool turningL, turningR;
        int stopLeft, stopRight;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class WandererController : public StateMachine, public AgentInterface {

        public:
        WandererController() : StateMachine() {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
                                                               // event name in case there are 
                                                               // multiple instances of this class
            add_transition("tick_nameL", moving_forward, rotatingL);
            add_transition("tick_nameL", rotatingL, moving_forward);
            add_transition("tick_nameR", moving_forward, rotatingR);
            add_transition("tick_nameR", rotatingR, moving_forward);
            add_transition("tick_name_straight", moving_forward, straighten);
            add_transition("tick_name_straight", straighten, moving_forward);
            moving_forward.set_tick_name("tick_nameL");
            rotatingL.set_tick_name(t"tick_nameL");
            rotatingR.set_tick_name(t"tick_nameR");
            straighten.set_tick_name("tick_name_straight");

        }

        MovingForward moving_forward;
        Straighten straighten;
        //Rotating rotating;
        RotatingL rotatingL;
        RotatingR rotatingR;
        std::string tick_name;

    };

    class Wanderer : public Agent {

        public:
        Wanderer(json spec, World& world) : Agent(spec, world) {
            add_process(wc);
        }

        WandererController wc;

    };

    DECLARE_INTERFACE(Wanderer);

}

#endif