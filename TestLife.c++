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
// Life
// ----

TEST(LifeFixture, constructor1) {
    istringstream i("....\n****\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 4.\n....\n****\n", w.str());
}

TEST(LifeFixture, constructor2) {
    istringstream i("....\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 0.\n....\n....\n", w.str());
}

TEST(LifeFixture, constructor3) {
	istringstream i("----\n0000\n");
	Life<FredkinCell> l(i, 2, 4);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 4.\n----\n0000\n", w.str());
}

TEST(LifeFixture, constructor4) {
	istringstream i("****\n....\n----\n0000\n");
	Life<Cell> l(i, 4, 4);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 8.\n****\n....\n----\n0000\n", w.str());
}

TEST(LifeFixture, constructor5) {
	istringstream i("*00.\n-.-*\n**..\n.0-*\n");
	Life<Cell> l(i, 4, 4);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 8.\n*00.\n-.-*\n**..\n.0-*\n", w.str());
}

TEST(LifeFixture, constructor6) {
	istringstream i("*\n");
	Life<Cell> l(i, 1, 1);
	ostringstream w;
	w << l;
	ASSERT_EQ("Generation = 0, Population = 1.\n*\n", w.str());
}

TEST(LifeFixture, simulateGeneration1) {
	istringstream i("....\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 0.\n....\n....\n", w.str());
}

TEST(LifeFixture, simulateGeneration2) {
	istringstream i("----\n----\n");
	Life<FredkinCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 0.\n----\n----\n", w.str());
}

TEST(LifeFixture, simulateGeneration3) {
	istringstream i("***.\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 2.\n.*..\n.*..\n", w.str());
}

TEST(LifeFixture, simulateGeneration4) {
	istringstream i(".***\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 2.\n..*.\n..*.\n", w.str());
}
TEST(LifeFixture, simulateGeneration5) {
	istringstream i("***.\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 2.\n.*..\n.*..\n", w.str());
}

TEST(LifeFixture, simulateGeneration6) {
	istringstream i(".***\n....\n");
	Life<ConwayCell> l(i, 2, 4);
	ostringstream w;
	l.simulateGeneration();
	w << l;
	ASSERT_EQ("Generation = 1, Population = 2.\n..*.\n..*.\n", w.str());
}

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
  ConwayCell c(true);
  ConwayCell c2(c);
  ASSERT_TRUE(c2._alive);
}

TEST(ConwayCellFixture, testCopyConstructor2) {
  ConwayCell c(true);
  ConwayCell c2(c);
  ASSERT_EQ(c2._symbol, '*');
}

TEST(ConwayCellFixture, testCopyConstructor3) {
  ConwayCell c(false);
  ConwayCell c2(c);
  ASSERT_EQ(c2._symbol, '.');
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
  ConwayCell c(true);
  ConwayCell* c3 = dynamic_cast<ConwayCell*>(c.clone());
  bool alive = c3->_alive;
  delete c3;
  ASSERT_TRUE(alive);
}

TEST(ConwayCellFixture, testClone2) {
  ConwayCell c(true);
  ConwayCell* c3 = dynamic_cast<ConwayCell*>(c.clone());
  char symbol = c3->_symbol;
  delete c3;
  ASSERT_EQ('*', symbol);
}

TEST(ConwayCellFixture, testClone3) {
  ConwayCell c(false);
  ConwayCell* c3 = dynamic_cast<ConwayCell*>(c.clone());
  char symbol = c3->_symbol;
  delete c3;
  ASSERT_EQ('.', symbol);
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
  FredkinCell c(true);
  FredkinCell c2(c);
  ASSERT_TRUE(c2._alive);
}

TEST(FredkinCellFixture, testCopyConstructor2) {
  FredkinCell c(true);
  FredkinCell c2(c);
  ASSERT_EQ(c2._symbol, '0');
}

TEST(FredkinCellFixture, testCopyConstructor3) {
  FredkinCell c(false);
  FredkinCell c2(c);
  ASSERT_EQ(c2._symbol, '-');
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
  FredkinCell c(true);
  FredkinCell* c3 = dynamic_cast<FredkinCell*>(c.clone());
  bool alive = c3->_alive;
  delete c3;
  ASSERT_TRUE(alive);
}

TEST(FredkinCellFixture, testClone2) {
  FredkinCell c(true);
  FredkinCell* c3 = dynamic_cast<FredkinCell*>(c.clone());
  char symbol = c3->_symbol;
  delete c3;
  ASSERT_EQ('0', symbol);
}

TEST(FredkinCellFixture, testClone3) {
  FredkinCell c(false);
  FredkinCell* c3 = dynamic_cast<FredkinCell*>(c.clone());
  char symbol = c3->_symbol;
  delete c3;
  ASSERT_EQ('-', symbol);
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

// ----
// Cell
// ----

TEST(CellFixture, constructor1) {
	Cell c;
	ASSERT_EQ(nullptr, c._p);
}

TEST(CellFixture, constructor2) {
	ConwayCell* cc = new ConwayCell();
	Cell c(cc);
	ASSERT_EQ(cc, c._p);
}

TEST(CellFixture, constructor3) {
	FredkinCell* fc = new FredkinCell();
	Cell c(fc);
	ASSERT_EQ(fc, c._p);
}

TEST(CellFixture, evolve1) {
	ConwayCell* cc = new ConwayCell(true);
	Cell c(cc);
	int population = 0;
	c.evolve(3, population);
	ASSERT_EQ(1, population);
}
TEST(CellFixture, evolve2) {
	ConwayCell* cc = new ConwayCell(true);
	Cell c(cc);
	int population = 0;
	c.evolve(2, population);
	ASSERT_EQ(1, population);
}

TEST(CellFixture, evolve3) {
	ConwayCell* cc = new ConwayCell(true);
	Cell c(cc);
	int population = 0;
	c.evolve(1, population);
	ASSERT_EQ(0, population);
}

TEST(CellFixture, evolve4) {
	ConwayCell* cc = new ConwayCell(true);
	Cell c(cc);
	int population = 0;
	c.evolve(8, population);
	ASSERT_EQ(0, population);
}

TEST(CellFixture, evolve5) {
	ConwayCell* cc = new ConwayCell(false);
	Cell c(cc);
	int population = 0;
	c.evolve(3, population);
	ASSERT_EQ(1, population);
}

TEST(CellFixture, evolve6) {
	ConwayCell* cc = new ConwayCell(false);
	Cell c(cc);
	int population = 0;
	c.evolve(0, population);
	ASSERT_EQ(0, population);
}

TEST(CellFixture, evolve7) {
	FredkinCell* fc = new FredkinCell(true);
	Cell c(fc);
	int population = 0;
	c.evolve(1, population);
	ASSERT_EQ(1, population);
}

TEST(CellFixture, evolve8) {
	FredkinCell* fc = new FredkinCell(true);
	Cell c(fc);
	int population = 0;
	c.evolve(0, population);
	ASSERT_EQ(0, population);
}

TEST(CellFixture, evolve9) { //conversion
	FredkinCell* fc = new FredkinCell(true);
	Cell c(fc);
	int population = 0;
	ASSERT_EQ(fc, c._p);
	c.evolve(3, population);
	ASSERT_EQ(1, population);
	ASSERT_EQ(fc, c._p);
	c.evolve(3, population);
	ASSERT_EQ(2, population);
	ASSERT_TRUE(fc != c._p);
}

TEST(CellFixture, calculateStatus1) {
	Cell c(new ConwayCell(true));
	ASSERT_EQ(true, c.calculateStatus());
}

TEST(CellFixture, calculateStatus2) {
	Cell c(new ConwayCell(false));
	ASSERT_EQ(false, c.calculateStatus());
}

TEST(CellFixture, calculateStatus3) {
	Cell c(new FredkinCell(true));
	ASSERT_EQ(true, c.calculateStatus());
}
TEST(CellFixture, calculateStatus4) {
	Cell c(new FredkinCell(false));
	ASSERT_EQ(false, c.calculateStatus());
}

TEST(CellFixture, copyConstructor1) {
	Cell c(new ConwayCell(true));
	Cell c2(c);
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyConstructor2) {
	Cell c(new ConwayCell(false));
	Cell c2(c);
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyConstructor3) {
	Cell c(new FredkinCell(true));
	Cell c2(c);
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyConstructor4) {
	Cell c(new FredkinCell(false));
	Cell c2(c);
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyAssignment1) {
	Cell c(new ConwayCell(true));
	Cell c2(new ConwayCell(false));
	c = c2;
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyAssignment2) {
	Cell c(new ConwayCell(true));
	Cell c2(new ConwayCell(false));
	c2 = c;
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyAssignment3) {
	Cell c(new FredkinCell(true));
	Cell c2(new FredkinCell(false));
	c = c2;
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}

TEST(CellFixture, copyAssignment4) {
	Cell c(new FredkinCell(true));
	Cell c2(new FredkinCell(false));
	c2 = c;
	ASSERT_EQ(c.calculateStatus(), c2.calculateStatus());
}
