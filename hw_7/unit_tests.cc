#include "gtest/gtest.h"
#include "elma/elma.h"
#include "power.h"
#include "microwave.h"
#include "robot.h"
#include "better_state_machine.h"
#include <iostream>

using namespace std::chrono;
using namespace elma;

namespace {
   
    TEST(Microwave, Safety) {

        Manager m;
        Power power;      
        Microwave microwave;

        m.schedule(power, 10_ms)
         .schedule(microwave, 10_ms)
         .init();

        m.start();
        m.emit(Event("on button pressed"));
        ASSERT_EQ(true, power.running);

        m.start();
        m.emit(Event("door opened"));    
        m.emit(Event("on button pressed"));
        ASSERT_EQ(false, power.running);

        // ETC

    }

    TEST(Robot, Basics) {

        Robot robot = Robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");  

        // ETC

    }

    TEST(BetterStateMachine, Basics) {

        BetterStateMachine fsm("toggle switch");  
        fsm.to_json();

        // ETC

    }

}
