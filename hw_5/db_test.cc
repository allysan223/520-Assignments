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

        try {
            db.find_by_name("pluto");                        
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find row by name");
        }

        ASSERT_EQ(NAME(db.find_by_name("earth")), "earth"); 
        ASSERT_EQ(NAME(db.find_by_name("jupiter")), "jupiter");   

        db.create_test_data(100); 

        ASSERT_EQ(NAME(db.find_by_name("exoplanet40")), "exoplanet40"); 

    }

}