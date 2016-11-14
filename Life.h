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
  virtual bool evolve(int n, int& pop) = 0;
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
    neighborCounts[row][col] += 1;
  }

  bool evolve(int n, int& pop) {
    if (_alive && (n < 2 || n > 3)) {
      _alive = false;
      _symbol = '.';
    } else if (!_alive && n == 3) {
      _alive = true;
      _symbol = '*';
      ++pop;
    }
    else if(_alive)
      ++pop;
    return false;
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
  	return new ConwayCell(*this);
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

  FredkinCell(const FredkinCell* rhs) : AbstractCell(rhs->_alive), _age(0) {
    _symbol = rhs->_alive? '0' : '-';
    delete rhs;
  };

  bool evolve(int n, int& pop) {
    if (_alive && (n == 0 || n == 2 || n == 4)) {
      _alive = false;
      _symbol = '-';
    } else if (!_alive && (n == 1 || n == 3)) {
      _alive = true;
      ++pop;
      if (_age >= 10) {
        _symbol = '+';
      } else {
        _symbol = '0' + _age; // converts int to char
      }
    } else if (_alive) {
      ++_age;
      ++pop;
      if (_age >= 10) {
        _symbol = '+';
      } else {
        _symbol = '0' + _age; // converts int to char
      }
    }
    return _age == 2;
  };

  bool calculateStatus() const {
    if (_symbol != '-' )
      return true;
    else
      return false;
  }

  void flag(vector<vector<int>>& neighborCounts, int row, int col)
  {
    return;
  }

  FredkinCell(const ConwayCell* rhs) : AbstractCell(false), _age(0)
  {};

  AbstractCell* clone() const {
  	return new FredkinCell(*this);
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

  void flag(vector<vector<int>>& neighborCounts, int row, int col)
  {
    _p->flag(neighborCounts, row, col);
  }

  void evolve(int n, int& pop) {
    bool convert = _p->evolve(n, pop);
    if(convert) {
      delete _p;
      _p = new ConwayCell(true);
    }
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
          ++_population;
        } else if (t == '-') {
          _grid[r][c] = T(new FredkinCell(false));
        } else {
          _grid[r][c] = T(new FredkinCell(true));
          ++_population;
        }
      }
    }
  };

  friend ostream& operator <<(ostream& o, const Life& l) {
    cout << "Generation = " << l._generation << ", Population = " << l._population << "." << endl;
    for (size_t r = 0; r < l._grid.size(); ++r) {
      for (size_t c = 0; c < l._grid[0].size(); ++c) {
        o << l._grid[r][c];
      }
      o << endl;
    }
    return o;
  };

  void simulateGeneration() {
    _population = 0; // resets Population

    // First pass: calculate neighborCounts
    for (size_t r = 0; r < _grid.size(); ++r) {
      for (size_t c = 0; c < _grid[0].size(); ++c) {
        if (_grid[r][c].calculateStatus()) {

          if (r-1 > 0) // top
            _neighborCounts[r-1][c] += 1;
          if (c+1 < _grid[0].size() - 1) // right
            _neighborCounts[r][c+1] += 1;
          if (r+1 < _grid.size() - 1) // bottom
            _neighborCounts[r+1][c] += 1;
          if (c-1 > 0) // left
            _neighborCounts[r][c-1] += 1;

          if (r-1 > 0 && c-1 > 0) // top left
            _grid[r-1][c-1].flag(_neighborCounts, r-1, c-1);
          if (r-1 > 0 && c+1 < _grid[0].size() - 1) // top right
            _grid[r-1][c+1].flag(_neighborCounts, r-1, c+1);
          if (r+1 < _grid.size() - 1 && c+1 < _grid[0].size() - 1) // bottom right
            _grid[r+1][c+1].flag(_neighborCounts, r+1, c+1);
          if (r+1 < _grid.size() - 1 && c-1 > 0) // bottom left
            _grid[r+1][c-1].flag(_neighborCounts, r+1, c-1);
        }
      }
    }

    // Second pass: evolve each cell based on neighborCounts
    for (size_t r = 0; r < _grid.size(); ++r) {
      for (size_t c = 0; c < _grid[0].size(); ++c) {
        _grid[r][c].evolve(_neighborCounts[r][c], _population);
        _neighborCounts[r][c] = 0;
      }
    }
    ++_generation;
  };
};
#endif // Life_h
