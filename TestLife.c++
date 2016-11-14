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