#include "gtest/gtest.h"
#include "elma/elma.h"
#include "power.h"
#include "microwave.h"
#include "robot.h"
#include "better_state_machine.h"
#include <iostream>

using namespace std::chrono;
using namespace elma;

class Trigger : public Process {
    public:
    Trigger() : Process("trigger") {}
    void init() {}
    void start() {}
    void update() { 
        std::cout << "switch at " << milli_time() << "\n";
        emit(Event("switch"));
    }
    void stop() {}
};

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
        Manager m;
        Trigger trigger;
        Mode off("off"), on("on");
        BetterStateMachine fsm("toggle switch");

        fsm.set_initial(off)
        .set_propagate(false)
        .add_transition("switch", off, on)
        .add_transition("switch", on, off);

        // m.schedule(trigger, 1_ms)
        // .schedule(fsm, 5_ms) // Doesn't matter since mode has empty update()
        // .init()
        // .run(11_ms);
 
        json j = fsm.to_json();
        std::cout << j.dump(4) << std::endl;

        ASSERT_EQ(j["name"], "toggle switch");
        ASSERT_EQ(j["states"].size(), 2);


        // ETC

    }

}
