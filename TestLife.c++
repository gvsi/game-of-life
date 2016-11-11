// --------------------------
// projects/life/TestLife.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"

#include "Life.h"

using namespace std;

// ----
// test
// ----

TEST(LifeFixture, test) {
    // Life<int> x;
    ASSERT_TRUE(true);
}

// TEST(LifeFixture, test2) {
// 	Life<ConwayCell> x(8,8);
// 	ASSERT_TRUE(true);
// }

TEST(ConwayCellFixture, constructor) {
	ConwayCell cc;
	ASSERT_TRUE(true);
}
