#include "db.h"
#include "gtest/gtest.h"

namespace {
    
    TEST(DB,Basics) {

        DB db;

        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

        ASSERT_EQ(NAME(db.find(0)), "earth");

        auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

        ASSERT_EQ(rows.size(), 2);

        try {
            db.drop(2)                        
              .find(2);  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
        }

        try {
            db.insert("earth", 10, 71);                        
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Name already exists");
        }   
    }

    TEST(DB,Size) {
      DB db;

      db.insert("earth", 1, 1)            
        .insert("mars", 0.11, 1.524)
        .insert("moon", 0.012, 1)
        .insert("exoplanet one", 1, 1054.4)
        .insert("jupiter", 318, 5.2);

      ASSERT_EQ(NAME(db.find(0)), "earth");

      auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

      ASSERT_EQ(rows.size(), 2);

      ASSERT_EQ(db.size(), 5);

      db.drop(3);
      ASSERT_EQ(db.size(), 4);
    }

    TEST(DB,RandomGenerator) {
      DB db;
      db.create_test_data(26); 

      //ASSERT_EQ(NAME(db.find_by_name("exoplanet40")), "exoplanet40");
    }

    TEST(DB,FindByName) {
      DB db;

      db.insert("earth", 1, 1)            
        .insert("mars", 0.11, 1.524)
        .insert("moon", 0.012, 1)
        .insert("exoplanet one", 1, 1054.4)
        .insert("jupiter", 318, 5.2);

      ASSERT_EQ(NAME(db.find_by_name("moon")), "moon");
      
      try {
        db.find_by_name("pluto");                        
        FAIL();
      } catch ( runtime_error e ) {
          ASSERT_STREQ(e.what(), "Could not find row by name");
      }

      ASSERT_EQ(NAME(db.find_by_name("earth")), "earth"); 
      ASSERT_EQ(NAME(db.find_by_name("jupiter")), "jupiter"); 
    }

    TEST(DB,Accumulate) {
      DB db;

      db.insert("earth", 1, 1)            
        .insert("mars", 10, 1.5)
        .insert("moon", 5, 1)
        .insert("exoplanet one", 5, 10)
        .insert("jupiter", 9, 5);

      double total_mass = db.accumulate([](DB::Row row) { return MASS(row); });
      double total_distance = db.accumulate([](DB::Row row) { return DISTANCE(row); });
      double total_key = db.accumulate([](DB::Row row) { return KEY(row); });

      ASSERT_EQ(total_mass, 30);
      ASSERT_EQ(total_distance, 18.5);
      ASSERT_EQ(total_key, 10);
    }

    TEST(DB,Average) {
      DB db;

      db.insert("earth", 1, 1)            
        .insert("mars", 10, 1.5)
        .insert("moon", 5, 1)
        .insert("exoplanet one", 5, 10)
        .insert("jupiter", 9, 5);

      ASSERT_EQ(db.average_distance(), 3.7);
      ASSERT_EQ(db.average_mass(), 6);
    }

  
  TEST(Random,randomString) {
    int size = 10;
    char* str = (char*)malloc(sizeof(char) * size);
    gen_random(str, size);
    cout << "RANDOM STRING: " << str << "\n";
  }

}