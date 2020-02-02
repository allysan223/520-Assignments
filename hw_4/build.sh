make clean
g++ -c unit_tests.cc -std=c++11
g++ -c main.cc -std=c++11
g++ -o test *.o -lgtest -lpthread
./test