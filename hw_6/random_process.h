#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;
    using namespace std;
    using namespace std::chrono;
    using std::vector;

    class RandomProcess : public Process {
        public:

        RandomProcess(std::string name) : Process(name) {}

        void init() {}

        void start() {
        
        }

        void update() {
            // if ( channel("link").nonempty() ) {
            //     force = channel("Throttle").latest();
            // }
            randomNum = ((double)rand() / (double)(RAND_MAX));
            channel("link").send(randomNum);
            cout << "latest random num: " << randomNum << "\n";
        }

        void stop() {}

        private:
        double randomNum;

    };  



}

