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

// ----
// ConwayCell
// ----
TEST(ConwayCellFixture, testConstructor1) {
  ConwayCell c(true);
  ASSERT_TRUE(c._alive);
}

TEST(ConwayCellFixture, testConstructor2) {
  ConwayCell c(true);
  ASSERT_EQ(c._symbol, '*');
}

TEST(ConwayCellFixture, testConstructor3) {
  ConwayCell c(false);
  ASSERT_EQ(c._symbol, '.');
}

TEST(ConwayCellFixture, testCopyConstructor1) {
  ConwayCell* c = new ConwayCell(true);
  ConwayCell* c2(c);
  ASSERT_TRUE(c2->_alive);
}

TEST(ConwayCellFixture, testCopyConstructor2) {
  ConwayCell* c = new ConwayCell(true);
  ConwayCell* c2(c);
  ASSERT_EQ(c2->_symbol, '*');
}

TEST(ConwayCellFixture, testCopyConstructor3) {
  ConwayCell* c = new ConwayCell(false);
  ConwayCell* c2(c);
  ASSERT_EQ(c2->_symbol, '.');
}

TEST(ConwayCellFixture, testFlag1) {
  ConwayCell c(true);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 1);
}

TEST(ConwayCellFixture, testFlag2) {
  ConwayCell c(false);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 1);
}

TEST(ConwayCellFixture, testFlag3) {
  ConwayCell c(false);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  neighborCounts[0][0] = 1;
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 2);
}

TEST(ConwayCellFixture, testEvolve1) {
  ConwayCell c(true);
  int pop = 10;
  c.evolve(1, pop);
  ASSERT_FALSE(c._alive);
}

TEST(ConwayCellFixture, testEvolve2) {
  ConwayCell c(true);
  int pop = 10;
  c.evolve(1, pop);
  ASSERT_EQ(c._symbol, '.');
}

TEST(ConwayCellFixture, testEvolve3) {
  ConwayCell c(false);
  int pop = 10;
  c.evolve(3, pop);
  ASSERT_TRUE(c._alive);
  ASSERT_TRUE(pop == 11);
}

TEST(ConwayCellFixture, testCalculateStatus1) {
  ConwayCell c(false);
  ASSERT_FALSE(c.calculateStatus());
}

TEST(ConwayCellFixture, testCalculateStatus2) {
  ConwayCell c(true);
  ASSERT_TRUE(c.calculateStatus());
}

TEST(ConwayCellFixture, testCalculateStatus3) {
  ConwayCell c(true);

  ASSERT_TRUE(c.calculateStatus());

  int pop = 10;
  c.evolve(1, pop);

  ASSERT_FALSE(c.calculateStatus());
}

TEST(ConwayCellFixture, testClone1) {
  ConwayCell* c = new ConwayCell(true);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_TRUE(c2->_alive);
}

TEST(ConwayCellFixture, testClone2) {
  ConwayCell* c = new ConwayCell(true);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_EQ(c2->_symbol, '*');
}

TEST(ConwayCellFixture, testClone3) {
  ConwayCell* c = new ConwayCell(false);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_EQ(c2->_symbol, '.');
}

TEST(ConwayCellFixture, testCopyAssignment1) {
  ConwayCell c = ConwayCell(true);
  ConwayCell c2 = ConwayCell(false);
  c2 = c;
  ASSERT_TRUE(c2._alive);
}

TEST(ConwayCellFixture, testCopyAssignment2) {
  ConwayCell c = ConwayCell(true);
  ConwayCell c2 = ConwayCell(false);
  c2 = c;
  ASSERT_EQ(c2._symbol, '*');
}

TEST(ConwayCellFixture, testCopyAssignment3) {
  ConwayCell c = ConwayCell(false);
  ConwayCell c2 = ConwayCell(true);
  c2 = c;
  ASSERT_EQ(c2._symbol, '.');
}

TEST(ConwayCellFixture, testPrint1) {
	ConwayCell c = ConwayCell(true);
	ostringstream w;
  c.print(w);

	ASSERT_EQ("*", w.str());
}

TEST(ConwayCellFixture, testPrint2) {
	ConwayCell c = ConwayCell(false);
	ostringstream w;
  c.print(w);

	ASSERT_EQ(".", w.str());
}

TEST(ConwayCellFixture, testPrint3) {
	ConwayCell c = ConwayCell(true);
	ostringstream w;
  c.print(w);
	ASSERT_EQ("*", w.str());
  int pop = 10;
  c.evolve(1, pop);
  ostringstream w2;
  c.print(w2);
  ASSERT_EQ(".", w2.str());
}

// ----
// FredkinCell
// ----
TEST(FredkinCellFixture, testConstructor1) {
  FredkinCell c(true);
  ASSERT_TRUE(c._alive);
}

TEST(FredkinCellFixture, testConstructor2) {
  FredkinCell c(true);
  ASSERT_EQ(c._symbol, '0');
}

TEST(FredkinCellFixture, testConstructor3) {
  FredkinCell c(false);
  ASSERT_EQ(c._symbol, '-');
}

TEST(FredkinCellFixture, testCopyConstructor1) {
  FredkinCell* c = new FredkinCell(true);
  FredkinCell* c2(c);
  ASSERT_TRUE(c2->_alive);
}

TEST(FredkinCellFixture, testCopyConstructor2) {
  FredkinCell* c = new FredkinCell(true);
  FredkinCell* c2(c);
  ASSERT_EQ(c2->_symbol, '0');
}

TEST(FredkinCellFixture, testCopyConstructor3) {
  FredkinCell* c = new FredkinCell(false);
  FredkinCell* c2(c);
  ASSERT_EQ(c2->_symbol, '-');
}

TEST(FredkinCellFixture, testFlag1) {
  FredkinCell c(true);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 0);
}

TEST(FredkinCellFixture, testFlag2) {
  FredkinCell c(false);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 0);
}

TEST(FredkinCellFixture, testFlag3) {
  FredkinCell c(false);
  vector<vector<int>> neighborCounts = vector<vector<int>>(3, vector<int>(3, 0));
  neighborCounts[0][0] = 1;
  c.flag(neighborCounts, 0, 0);
  ASSERT_EQ(neighborCounts[0][0], 1);
}

TEST(FredkinCellFixture, testEvolve1) {
  FredkinCell c(true);
  int pop = 10;
  c.evolve(2, pop);
  ASSERT_FALSE(c._alive);
}

TEST(FredkinCellFixture, testEvolve2) {
  FredkinCell c(true);
  int pop = 10;
  c.evolve(2, pop);
  ASSERT_EQ(c._symbol, '-');
}

TEST(FredkinCellFixture, testEvolve3) {
  FredkinCell c(false);
  int pop = 10;
  c.evolve(3, pop);
  ASSERT_TRUE(c._alive);
  ASSERT_TRUE(pop == 11);
}

TEST(FredkinCellFixture, testCalculateStatus1) {
  FredkinCell c(false);
  ASSERT_FALSE(c.calculateStatus());
}

TEST(FredkinCellFixture, testCalculateStatus2) {
  FredkinCell c(true);
  ASSERT_TRUE(c.calculateStatus());
}

TEST(FredkinCellFixture, testCalculateStatus3) {
  FredkinCell c(true);

  ASSERT_TRUE(c.calculateStatus());

  int pop = 10;
  c.evolve(2, pop);

  ASSERT_FALSE(c.calculateStatus());
}

TEST(FredkinCellFixture, testClone1) {
  FredkinCell* c = new FredkinCell(true);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_TRUE(c2->_alive);
}

TEST(FredkinCellFixture, testClone2) {
  FredkinCell* c = new FredkinCell(true);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_EQ(c2->_symbol, '0');
}

TEST(FredkinCellFixture, testClone3) {
  FredkinCell* c = new FredkinCell(false);
  AbstractCell* c2 = c->clone();
  delete c;
  ASSERT_EQ(c2->_symbol, '-');
}

TEST(FredkinCellFixture, testCopyAssignment1) {
  FredkinCell c = FredkinCell(true);
  FredkinCell c2 = FredkinCell(false);
  c2 = c;
  ASSERT_TRUE(c2._alive);
}

TEST(FredkinCellFixture, testCopyAssignment2) {
  FredkinCell c = FredkinCell(true);
  FredkinCell c2 = FredkinCell(false);
  c2 = c;
  ASSERT_EQ(c2._symbol, '0');
}

TEST(FredkinCellFixture, testCopyAssignment3) {
  FredkinCell c = FredkinCell(false);
  FredkinCell c2 = FredkinCell(true);
  c2 = c;
  ASSERT_EQ(c2._symbol, '-');
}

TEST(FredkinCellFixture, testPrint1) {
	FredkinCell c = FredkinCell(true);
	ostringstream w;
  c.print(w);

	ASSERT_EQ("0", w.str());
}

TEST(FredkinCellFixture, testPrint2) {
	FredkinCell c = FredkinCell(false);
	ostringstream w;
  c.print(w);

	ASSERT_EQ("-", w.str());
}

TEST(FredkinCellFixture, testPrint3) {
	FredkinCell c = FredkinCell(true);
	ostringstream w;
  c.print(w);
	ASSERT_EQ("0", w.str());
  int pop = 10;
  c.evolve(2, pop);
  ostringstream w2;
  c.print(w2);
  ASSERT_EQ("-", w2.str());
}

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
