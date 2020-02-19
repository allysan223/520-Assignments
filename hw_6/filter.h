#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;
    using namespace std;
    using namespace std::chrono;
    using std::vector;

    class Filter : public Process {
        public:

        Filter(std::string name) : Process(name) {}

        void init() {
            total = 0;
            totalIter = 0;
            index = 0;
            buffer = vector<double>(10, 0);
        }

        void start() {
        
        }

        void update() {
            total = 0;
            
            cout << "filter - update \n" ;
            if (channel("link").empty()){
                //cout << "filter - channel link empty \n" ;
                total = 0;
                return; 
            }
            //cout << "filter - not empty" << ", size: " << channel("link").size() << " \n" ;
            buffer[index] = (channel("link").latest());
            
            //stop count at 10 (denominator for calculating average)
            if (totalIter < 10){
                totalIter++;    
            }
            
            index++;
            if (index == 10){
                index = 0;
            }

            for (int i = 0; i< buffer.size(); i++){
                //cout << "buffer, index: " << i << ", value: " << buffer[i] << "\n";
                total += buffer[i];
            } 

            //cout << "count: " << totalIter << ", total: " << total << ", average: " << value() << "\n";
        }

        void stop() {}


        double value(){
            return total/(double)totalIter;
        }

        private:
        double total;
        double latestVal;
        int index;
        int totalIter;
        vector<double> buffer;


    };  



}

