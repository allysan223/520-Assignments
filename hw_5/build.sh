make clean
g++ -c examples.cc -std=c++17
g++ -c arith_test.cc -std=c++17
g++ -c db.cc -std=c++17
g++ -c db_test.cc -std=c++17
g++ -c unit_tests.cc -std=c++17
g++ -c main.cc -std=c++17
g++ -o test *.o -lgtest -lpthread
./test
