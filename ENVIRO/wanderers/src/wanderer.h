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
            track_velocity(2,0);
            if ( sensor_value(0) < 10  && sensor_value(2) > 15) { //turn left 90
                std::cout << "FRONT SENSOR LESS THAN 10, sensor 0: "<< sensor_value(0) << ", sensor value 2: " << sensor_value(2) << "\n";
                emit(Event(tick_name));
            }
            if ( sensor_value(0) > 10  && sensor_value(2) < 9) { //turn right little
                std::cout << "FRONT SENSOR LESS THAN 10, straighten to right "<< "\n";
                emit(Event("tick_name_straight"));
            }
            if ( sensor_value(0) > 10  && sensor_value(1) < 9) { //turn left little
                std::cout << "FRONT SENSOR LESS THAN 10, straighten to left "<< "\n";
                emit(Event("tick_name_straight"));
            }
      
        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    // class Rotating : public State, public AgentInterface {
    //     public:
    //     void entry(const Event& e) {
    //         angle = M_PI/2+.5;
    //         turningL = false;
    //         turningR = false;
    //         apply_force(-50, 0);
    //     } //{ rate = rand() % 2 == 0 ? 2 : -2; }
    //     void during() { 
    //         if ( sensor_value(0) > 50  && (!turningL && !turningR)) {
    //             emit(Event(tick_name));
    //         }
            
    //         if ( sensor_value(2) > sensor_value(1) && sensor_value(2) > sensor_value(0) && (sensor_value(1) - sensor_value(2) < 10)) { //left sensor
    //         //apply_force(0,-angle);
    //         turningL = true;
    //         track_velocity(0,-angle);
    //         std::cout << "TURNN LEFTTT DURING \n";
    //         } else if (sensor_value(1) > sensor_value(2) && sensor_value(1) > sensor_value(0)) { //right sensor
    //             std::cout << "TURNN RIGHTT DURING \n";
    //             turningR = true;
    //             track_velocity(0,angle);
    //             //apply_force(0,angle);
    //         } 
            
    //         if (turningL)
    //             track_velocity(0,-angle);
    //         if (turningR)
    //             track_velocity(0,angle);
            
    //         turningL = false;
    //         turningR = false;
    //         std::cout << "LEFT SENSOR: "<<  sensor_value(2) << " RIGHT SENSOR: " << sensor_value(1) << "\n";

    //     }
    //     void exit(const Event& e) {}
    //     double rate, angle;
    //     bool turningL, turningR;
    //     int stopLeft, stopRight;
    //     void set_tick_name(std::string s) { tick_name = s; }
    //     std::string tick_name;        
    // };

    class RotatingL : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            std::cout << "START TURNN LEFTTT: " << angle() << "\n";
            apply_force(-45, 0);
            startAngle = angle();
        } //{ rate = rand() % 2 == 0 ? 2 : -2; }
        void during() {
            //back up if too close to wall while turning
            if (sensor_value(0) < 8 && sensor_value(3) > 20){
                apply_force(-10, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                std::cout << "Turning left, back up " << "\n";
            }
            //turn robot ccw
            if ( angle() <= startAngle - M_PI/2 +.05 ) {
                track_velocity(.05,-0.1);
                emit(Event(tick_name));
            }
            prevSensorVal = sensor_value(0);
            track_velocity(.05,-0.1);
            angleVal = angle();
            std::cout << "TURNN LEFTTT GOAL: " << startAngle - M_PI/2 << "\n";
            std::cout << "TURNN LEFTTT: " << angle() << " ,sensor 0: " << sensor_value(0) << " ,sensor 3: " << sensor_value(3) << "\n";
        }
        void exit(const Event& e) {}
        double rate, angleVal, startAngle, prevSensorVal;
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
            add_transition(tick_name, moving_forward, rotatingL);
            add_transition(tick_name, rotatingL, moving_forward);
            add_transition("tick_name_straight", moving_forward, straighten);
            add_transition("tick_name_straight", straighten, moving_forward);
            moving_forward.set_tick_name(tick_name);
            rotatingL.set_tick_name(tick_name);
            straighten.set_tick_name("tick_name_straight");

        }

        MovingForward moving_forward;
        Straighten straighten;
        //Rotating rotating;
        RotatingL rotatingL;
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