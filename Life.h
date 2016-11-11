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

class AbstractCell {
friend ostream& operator <<(ostream& o, const AbstractCell& ac) {
  return ac.print(o);
}
protected:
  bool _alive;
public:
  AbstractCell(bool alive) :
    _alive(alive)
  {};
  virtual void evolve(int n) = 0;
  virtual AbstractCell* clone() const = 0;
  virtual ~AbstractCell() {};
  virtual ostream& print(ostream& o) const = 0;
};

class ConwayCell : AbstractCell {
friend ostream& operator <<(ostream& o, const ConwayCell& cc) {
  return cc.print(o);
}
public:
  ConwayCell(bool alive = false) :
    AbstractCell(alive)
    {};

  void evolve(int n) {

  };

  AbstractCell* clone() const {
  	return new ConwayCell(_alive);
  };

  ConwayCell& operator =(ConwayCell* cp) {
    cout << "called";
    _alive = cp->_alive;
    return *this;
  }

  ostream& print(ostream& o) const {
    if (_alive) {
      o << "*";
    } else {
      o << ".";
    }
    return o;
  }
};

class FredkinCell : AbstractCell {
friend ostream& operator <<(ostream& o, const FredkinCell& fc) {
  return fc.print(o);
}
private:
  int _age;
public:
  FredkinCell(bool alive = false, int age = 0) :
    AbstractCell(alive),
    _age(age)
    {};

  void evolve(int n) {

  };

  AbstractCell* clone() const {
  	return new FredkinCell(_alive, _age);
  };

  ostream& print(ostream& o) const {
    if (_alive) {
      if (_age >= 10) {
        o << "+";
      } else {
        o << _age;
      }
    } else {
      o << "-";
    }
    return o;
  }
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

  friend ostream& operator <<(ostream& o, const Cell& c) {
    o << *(c._p);
    return o;
  }
};

template <typename T>
class Life {
private:
  vector<vector<T*>> _grid;
  vector<vector<int>> _neighborCounts;
  int _generation, _population;
public:
  bool dummy () {
    return true;}
  Life(istream& input, int rows, int cols) :
  _grid(vector<vector<T*>>(rows, vector<T*>(cols))),
  _neighborCounts(vector<vector<int>>(rows, vector<int>(cols, 0))),
  _generation(0),
  _population(0)
  {
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        char t;
        input >> t;

        if (t == '.') {
          ConwayCell cc = ConwayCell(false);
          _grid[r][c] = cc.clone();
        } else if (t == '*') {
          ConwayCell cc = ConwayCell(true);
          _grid[r][c] = cc.clone();
        } else if (t == '+') {
          FredkinCell fc = FredkinCell(true);
          _grid[r][c] = fc.clone();
        } else if (t == '-') {
          FredkinCell fc = FredkinCell(false);
          _grid[r][c] = fc.clone();
        } else {
          FredkinCell fc = FredkinCell(true, 0);
          _grid[r][c] = fc.clone();
        }
      }
    }
    cout << *this;
  };

  friend ostream& operator <<(ostream& o, const Life& l) {
    for (size_t r = 0; r < l._grid.size(); ++r) {
      for (size_t c = 0; c < l._grid[0].size(); ++c) {
        o << l._grid[r][c];
        // o << r << c << " ";
      }
      o << endl;
    }
    return o;
  }

  void simulateGeneration() {
  }
};
#endif // Life_h
