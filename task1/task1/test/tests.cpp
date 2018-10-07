    #include <fstream>
   
   #include "gmock/gmock.h"
   #include "gtest/gtest.h"
   #include "TritSet.h"
   #include "Other.h"
   
   TEST (basic_tests, if_eq) {
       ASSERT_EQ(1,1);
   }
   
   TEST (tritset_tests, create) {
       ASSERT_EQ(TritSet().get_size(), 0);
       ASSERT_EQ(TritSet().get_last_i(), -1);
       ASSERT_EQ(TritSet(100).get_size(), 100 * 2 / sizeof(uint) / 8 + 1);
       ASSERT_EQ(TritSet(18).get_size(), 18 * 2 / sizeof(uint) / 8 + 1);
       ASSERT_EQ(TritSet(100).get_last_i(), -1);
       TritSet some(20);
       TritSet other = some;
       ASSERT_EQ(other.get_size(), some.get_size());
       ASSERT_EQ(other.get_last_i(), -1);
   } 
   
   TEST (tritset_tests,getsize)
   {
       TritSet some (30);
       ASSERT_EQ(some.get_size(), 30 * 2 / sizeof(uint) / 8 + 1);
   }
   
  
   TEST(trit_set_test, cut_to_trit)
   {
       TritSet some(20);
       some[10] = True;
       some[12] = False;
       some.cut_to_trit(12);
       ASSERT_EQ(some.get_last_i(), 12);
       ASSERT_EQ(some.get_size(), 11 * 2 / sizeof(uint) / 8 + 1);
       ASSERT_EQ(some[10], True);
       ASSERT_EQ(some[12], Unknown);
   }
   
   TEST(trit_set_test, shrink)
   {
   	TritSet some(20);
   	some.shrink();
   	ASSERT_EQ(some.get_size(), 0);
   	TritSet other(30);
   	other[15] = True;
   	other.shrink();
   	ASSERT_EQ(other.get_size(), 15 * 2 / sizeof(uint) / 8 + 1);
   	ASSERT_EQ(other[15], Unknown);
   }
   
   TEST(trit_set_test, trim)
   {
   	TritSet some(5);
   	for (int i = 0; i < 5; i++)
   		some[i] = True;
   	some.trim(3);
   	ASSERT_EQ(some[2], True);
   	ASSERT_EQ(some[4], Unknown);
   	ASSERT_EQ(some.get_last_i(), 3);
   }
   
   TEST(trit_set_test, cardinality)
   {
   	TritSet some(10);
   	for (int i = 0; i < 6; i++)
   		some[i] = True;
   	some[6] = False;
   	some[9] = False;
   	ASSERT_EQ(some.cardinality(True), 6);
   	ASSERT_EQ(some.cardinality(False), 2);
   	ASSERT_EQ(some.cardinality(Unknown), 2);
   }
   
   TEST(trit_set_test, cardinality_map)
   {
   	TritSet some(10);
   	for (int i = 0; i < 6; i++)
   		some[i] = True;
   	some[6] = False;
   	some[9] = False;
   	std::unordered_map<trit, uint> result = some.cardinality();
   	ASSERT_EQ(result[True], 6);
   	ASSERT_EQ(result[False], 2);
   	ASSERT_EQ(result[Unknown], 2);
   }
   
   TEST(reference_test, equality)
   {
   	TritSet some(2);
   	some[0] = True; 
   	 ASSERT_EQ(some[0] == True, true);
   	 ASSERT_EQ(some[0] == False, false);
   	some[1] = False;
   	 ASSERT_EQ(some[1] == some[0], false);
   }
   
   TEST(reference_test, n_equality)
   {
   	TritSet some(2);
   	some[0] = False;
   	 ASSERT_EQ(some[0] != True, true);
   	 ASSERT_EQ(some[0] != False, false);
   	some[1] = False;
   	 ASSERT_EQ(some[1] != some[0], false);
   }
   
   int main(int argc, char **argv) {
       ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
   }
 
