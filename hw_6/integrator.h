#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;
    using namespace std;
    using namespace std::chrono;
    using std::vector;

    class Integrator : public Process {
        public:

        Integrator(std::string name) : Process(name) {}

        void init() {
            integratedVal = 0;
        }

        void start() {
        
        }

        void update() {
            // if ( channel("link").nonempty() ) {
            //     force = channel("Throttle").latest();
            // }
            v = (channel("link").latest());
            integratedVal += v * delta();
            //cout << "delta: " << delta() << ", latest num: " << v << "\n";

        }

        void stop() {}

        double value() {
            return integratedVal;
        }

        private:
        double v; //stores value from "link" channel
        double integratedVal; //stores integrated value

    };  



}

