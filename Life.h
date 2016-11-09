// --------------------
// projects/life/Life.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------

#include <vector>

#ifndef Life_h
#define Life_h

using namespace std;

template <typename T>
class Life {
private:
  vector<vector<T>> _grid;
  vector<vector<int>> _neighborCounts;
  int generation, population;
public:
  bool dummy () {
    return true;}
  Life(int rows = 0, int cols = 0) :
  _grid(vector<vector<T>>(rows, vector<T>(cols, T()))),
  _neighborCounts(vector<vector<int>>(rows, vector<int>(cols, 0))),
  generation(0),
  population(0)
  {};

  void simulateGeneration() {

  }
};

class AbstractCell {
protected:
  bool _alive;
public:
  AbstractCell(bool alive) :
    _alive(alive)
  {};
  virtual void evolve(int n) = 0;
  virtual AbstractCell* clone() const;
  virtual ~AbstractCell();
};

class ConwayCell : AbstractCell {
public:
  ConwayCell(bool alive = false) :
    AbstractCell(alive)
    {};

  void evolve(int n) {

  };

  ConwayCell* clone() const {
  	return new ConwayCell(_alive);
  };

//  ~ConwayCell(){};
};

class FredkinCell : AbstractCell {
private:
  int _age;
public:
  FredkinCell(bool alive = false, int age = 0) :
    AbstractCell(alive),
    _age(age)
    {};

  void evolve(int n) {
  	
  };

  FredkinCell* clone() const {
  	return new FredkinCell(_alive, _age);
  };

//  ~FredkinCell(){};
};

class Cell {
private:
  AbstractCell* _p;
public:

  Cell() :
  	_p(nullptr)
  {};

  Cell(AbstractCell* p) :
    _p(p)
  {};

  Cell(const Cell& rhs) :
  	_p(rhs._p == nullptr? nullptr : rhs._p->clone())
  {};

  Cell& operator = (const Cell& ac) {
  	_p = ac._p->clone();
  	return *this;
  };

  ~Cell() {
    delete _p;
  };
};
#endif // Life_h
