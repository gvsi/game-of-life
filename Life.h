// --------------------
// projects/life/Life.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------

#include <vector>
#include <algorithm>

#ifndef Life_h
#define Life_h

using namespace std;

class FredkinCell;

class AbstractCell {
friend ostream& operator <<(ostream& o, const AbstractCell& ac) {
  return ac.print(o);
}
protected:
  bool _alive;
  char _symbol;
public:
  AbstractCell(bool alive) :
    _alive(alive),
    _symbol('/')
  {};
  virtual void flag(vector<vector<int>>& neighborCounts, int row, int col) = 0;
  virtual void evolve(int n) = 0;
  virtual bool calculateStatus() const = 0;
  virtual AbstractCell* clone() const = 0;
  virtual ~AbstractCell() {};
  virtual ostream& print(ostream& o) const = 0;
};

class ConwayCell : public AbstractCell {
friend ostream& operator <<(ostream& o, const ConwayCell& cc) {
  return cc.print(o);
}
public:
  ConwayCell(bool alive = false) :
    AbstractCell(alive)
  {
    _symbol = _alive? '*' : '.';
  };

  ConwayCell(const ConwayCell* rhs) : AbstractCell(rhs->_alive) {
    _symbol = rhs->_alive? '*' : '.';
    delete rhs;
  };

  void flag(vector<vector<int>>& neighborCounts, int row, int col) {
    if(!_alive)
      return;

    bool leftWall;
    bool rightWall;
    bool topWall;
    bool bottomWall;
    if(row == 0)
      topWall = true;
    if(col == 0)
      leftWall = true;
    if((size_t)row == neighborCounts.size() -1)
      bottomWall = true;
    if((size_t)col == neighborCounts[0].size() -1)
      rightWall = true;

    if(!leftWall && !topWall) {
      //if (neighborCounts[col]) {

      //}
    }
  }

  void evolve(int n) {

  };

  bool calculateStatus() const {
    if (_symbol == '*') 
      return true;
    else
      return false;
  }

  ConwayCell& operator = (const ConwayCell& rhs) {
    _alive = rhs._alive;
    _symbol = rhs._symbol;
    return *this;
  };

  ConwayCell(const FredkinCell* rhs) : AbstractCell(false) {
  };

  AbstractCell* clone() const {
  	return new ConwayCell(_alive);
  };

  ostream& print(ostream& o) const {
    return o << _symbol;
  };

  ~ConwayCell()
  {
  };
};

class FredkinCell : public AbstractCell {
friend ostream& operator <<(ostream& o, const FredkinCell& fc) {
  return fc.print(o);
}
private:
  int _age;
public:
  FredkinCell(bool alive = false) :
    AbstractCell(alive),
    _age(0)
  {
    _symbol = _alive? '0' : '-';
  };

    FredkinCell(const FredkinCell* rhs) : AbstractCell(rhs->_alive) {
    _symbol = rhs->_alive? '0' : '-';
    _age = 0;
    delete rhs;
  };

  void evolve(int n) {

  };

  bool calculateStatus() const {
    if (_symbol != '-' ) 
      return true;
    else
      return false;
  }

  void flag(vector<vector<int>>& neighborCounts, int row, int col)
  {
    
  }

  FredkinCell(const ConwayCell* rhs) : AbstractCell(false), _age(0)
  {};

  AbstractCell* clone() const {
  	return new FredkinCell(_alive);
  };

  ostream& print(ostream& o) const {
    return o << _symbol;
  };
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

  bool calculateStatus() const {
    return _p->calculateStatus();
  }

  ~Cell() {
    delete _p;
  };

  friend ostream& operator <<(ostream& o, const Cell& c) {
    return o << *(c._p);
  };
};

template <typename T>
class Life {
private:
  vector<vector<T>> _grid;
  vector<vector<int>> _neighborCounts;
  int _generation, _population;
public:
  bool dummy () {
    return true;}

  Life(istream& input, int rows, int cols) :
  _grid(vector<vector<T>>(rows, vector<T>(cols))),
  _neighborCounts(vector<vector<int>>(rows, vector<int>(cols, 0))),
  _generation(0),
  _population(0)
  {
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        char t;
        input >> t;

        if (t == '.') {
          _grid[r][c] = T(new ConwayCell(false));
        } else if (t == '*') {
          _grid[r][c] = T(new ConwayCell(true));
        } else if (t == '-') {
          _grid[r][c] = T(new FredkinCell(false));
        } else {
          _grid[r][c] = T(new FredkinCell(true));
        }
      }
    }
  };

  friend ostream& operator <<(ostream& o, const Life& l) {
    for (size_t r = 0; r < l._grid.size(); ++r) {
      for (size_t c = 0; c < l._grid[0].size(); ++c) {
        o << l._grid[r][c];
      }
      o << endl;
    }
    return o;
  };

  void simulateGeneration() {
    for (size_t r = 0; r < _grid.size(); ++r) {
      for (size_t c = 0; c < _grid[0].size(); ++c) {
        _grid[r][c].calculateStatus();

      }
    }
  };
};
#endif // Life_h
