#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 
#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include <math.h>
#include "enviro.h"
using namespace std::chrono;

double targetAngle = 0.0; 

namespace {

    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "MOVING FORWARD.. "<< "\n";
            if ( sensor_value(0) < 100){
                speed = 2;
                std::cout << " GO SLOWWWW \n";
            } else {
                speed = 10;
            }
            track_velocity(speed,0);
        }
        void during() { 
            if ( sensor_value(0) < 100){
                speed = 2;
            }

            if ( sensor_value(0) < 6  && sensor_value(2) > 15) { //turn left 90
                std::cout << "FRONT SENSOR LESS THAN 10, sensor 0: "<< sensor_value(0) << ", sensor value 2: " << sensor_value(2) << "\n";
                emit(Event("turn_left"));
            } else if (sensor_value(0) < 6) {
                emit(Event("turn_right"));
            }

            if ( angle() > targetAngle ) { //turn right little
                std::cout << "MOVING FORWARD, straighten to right "<< "\n";
                track_velocity(speed,-0.05);
                //emit(Event("tick_name_straight"));
            }

            if ( angle() < targetAngle) { //turn left little
                std::cout << "MOVING FORWARD, straighten to left "<< "\n";
                track_velocity(speed,0.05);
                //emit(Event("tick_name_straight"));
            }
      
        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        double speed;
        std::string tick_name;
    };

    class Rotating : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            event = e.name();
            std::cout << "EVENT: " << event << ", START TURNN LEFTTT: " << angle() << "\n";
            //apply_force(-45, 0);
            startAngle = angle();
            step = 0;
            //targetAngle = startAngle - M_PI/2;
            //targetAngle = event == "turn_right" ? startAngle + M_PI/2 : startAngle - M_PI/2;
            targetAngle = event == "turn_right" ? targetAngle + M_PI/2 : targetAngle - M_PI/2;
        } //{ rate = rand() % 2 == 0 ? 2 : -2; }
        void during() {
            //back up if too close to wall while turning
            if (step == 0 ){
                track_velocity(-.5,0);
                //turn robot ccw
                if ( sensor_value(0) >= 7 ) {
                    step = 1;
                //emit(Event(tick_name));
                 }
            }
            if (step == 1){
                event == "turn_right" ? track_velocity(.05,1) : track_velocity(.05,-1);
                
                //turn robot ccw
                if (event == "turn_left" && angle() <= targetAngle || event == "turn_right" && angle() >= targetAngle){
                     step = 2;
                 }
            }
            if ( step == 2 ) {
                //track_velocity(.05,0.05);
                event == "turn_right" ? track_velocity(.05,-0.1) : track_velocity(.05,0.1);
                condition = event == "turn_left" && angle() >= targetAngle || event == "turn_right" && angle() <= targetAngle;
                if (condition){
                    //turn again if still facing wall
                    if (sensor_value(0) < 6){
                        event == "turn_right" ? emit(Event("turn_right")) : emit(Event("turn_left"));
                    }
                    event == "turn_right" ? emit(Event("turn_right")) : emit(Event("turn_left"));
                }
            }

            angleVal = angle();
            std::cout << "TURNN LEFTTT GOAL: " << targetAngle << "\n";
            std::cout << "TURNN LEFTTT: " << angle() << " ,sensor 0: " << sensor_value(0) << " ,sensor 3: " << sensor_value(3) << "\n";
        }
        void exit(const Event& e) {}
        double rate, angleVal, startAngle;
        bool condition;
        std::string event;
        int step;
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

            if(sensor_value(2) > sensor_value(1)){
                track_velocity(0,-0.1);
                std::cout << "START STRAIGHTEN LEFT " << "\n";
            } else {
                track_velocity(0,0.1);
                std::cout << "START STRAIGHTEN RIGHT " << "\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
            add_transition("turn_left", moving_forward, rotating);
            add_transition("turn_left", rotating, moving_forward);
            add_transition("turn_right", moving_forward, rotating);
            add_transition("turn_right", rotating, moving_forward);
            add_transition("tick_name_straight", moving_forward, straighten);
            add_transition("tick_name_straight", straighten, moving_forward);
            //moving_forward.set_tick_name(tick_name);
            //rotating.set_tick_name("turn_left");
            //straighten.set_tick_name("tick_name_straight");

        }

        MovingForward moving_forward;
        Straighten straighten;
        Rotating rotating;
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