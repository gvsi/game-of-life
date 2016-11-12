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

#include <sstream>

using namespace std;

// ----
// test
// ----

TEST(LifeFixture, test) {
    // Life<int> x;
    ASSERT_TRUE(true);
}

TEST(LifeFixture, test2) {
	istringstream i("....\n****\n");
	Life<ConwayCell> l(i, 2,4);
	ostringstream w;
	w << l;
	ASSERT_EQ("....\n****\n", w.str());
}

// TEST(LifeFixture, test2) {
// 	Life<ConwayCell> x(8,8);
// 	ASSERT_TRUE(true);
// }

TEST(ConwayCellFixture, constructor) {
	ConwayCell cc;
	ASSERT_TRUE(true);
}