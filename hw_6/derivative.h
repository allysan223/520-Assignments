#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;
    using namespace std;
    using namespace std::chrono;
    using std::vector;

    class Derivative : public Process {
        public:

        Derivative(std::string name) : Process(name) {}

        void init() {
            x_k = 0;
            x_kPrev = 0;
            iterVal = 0;
        }

        void start() {
        
        }

        void update() {
            if ( channel("link").empty() ) {
                return;
            }
            x_kPrev = x_k;
            x_k = (channel("link").latest());
            //( x(k) - x(k-1) ) / delta()
            derivedVal = (x_k - x_kPrev) / delta();
            cout << "delta: " << delta() << ", current num: " << x_k << ", prev num: " << x_kPrev;
            cout << ", derived value: " << value() << "\n";

            iterVal++;

        }

        void stop() {}

        double value() {
            if (iterVal > 0)
                return derivedVal;
            //else
            return 0;
        }

        private:
        double x_k; //stores value from "link" channel (current value)
        double x_kPrev; //stores value from "link" channel (previous value)
        int iterVal; //counter to check if process has read atleast 2 values
        double derivedVal; //stores integrated value

    };  



}

