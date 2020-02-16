#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include "derivative.h"
//#include <channel.h>
#include <iostream>

#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(10))

namespace {

    using namespace elma;

    class DoNothing : public Process {
      public:
        DoNothing(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };   
    
    // TEST(Elma,Basics) {

    //   Manager m;
    //   DoNothing p("Do Nothing");

    //   m.schedule(p, 1_ms)    // process updates every 1ms
    //     .init()              // initialize all processes
    //     .run(10_ms);         // run for 1s

    // }

    // class MyProcess : public elma::Process {
    //   public:
    //     MyProcess(std::string name) : Process(name) {}
    //     void init() {}
    //     void start() {}
    //     void update() { 
    //       std::cout << name() << ": " 
    //                 << milli_time()
    //                 << "ms\n";
    //     }
    //     void stop() {}
    // };    

    // TEST(Elma,NumUpdates) {
    //     Manager m;
    //     MyProcess p("A"), q("B");

    //     m.schedule(p, 1_ms)
    //      .schedule(q, 5_ms)
    //      .init()
    //      .run(11_ms);

    //     ASSERT_EQ(p.num_updates(), 10);
    //     ASSERT_EQ(q.num_updates(), 2);      
    // }

    TEST(Stopwatch,count) {
      Stopwatch s;
      s.start();
      SLEEP;
      SLEEP;
      s.stop();   
      s.get_milliseconds();
      s.start();
      SLEEP;
      s.stop();
      s.get_milliseconds();
      s.reset();
      SLEEP;
      s.start();
      SLEEP;
      s.stop();
      s.get_milliseconds();
    }

    TEST(Elma,RandomProcess) {

      elma::Manager m;

      RandomProcess r("random numbers");
      Filter f("filter");
      Channel link("link");

      m.schedule(r, 1_ms)
       .schedule(f, 1_ms)
      .add_channel(link)
      .init()
      .run(30_ms);

      cout << "filtered average: " << f.value() << "\n";
    }

    TEST(Elma,Integrator) {

      elma::Manager m;

      RandomProcess r("random numbers");
      Integrator i("integrator");
      Channel link("link");
      m.schedule(r, 1_ms)
       .schedule(i, 1_ms)
      .add_channel(link)
      .init()
      .run(30_ms);

      cout << "integrated value: " << i.value() << "\n";
    }

    TEST(Elma,Derivative) {

      elma::Manager m;

      RandomProcess r("random numbers");
      Derivative d("derivative");
      Channel link("link");
      m.schedule(r, 1_ms)
       .schedule(d, 1_ms)
      .add_channel(link)
      .init()
      .run(30_ms);

      cout << "derived value: " << d.value() << "\n";
    }

}