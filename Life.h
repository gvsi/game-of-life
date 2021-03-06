// --------------------
// projects/life/Life.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------

#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#ifndef Life_h
#define Life_h

using namespace std;

class FredkinCell;

class AbstractCell {
  friend ostream &operator<<(ostream &o, const AbstractCell &ac) {
    return ac.print(o);
  }

protected:
  FRIEND_TEST(ConwayCellFixture, testConstructor1);
  FRIEND_TEST(ConwayCellFixture, testConstructor2);
  FRIEND_TEST(ConwayCellFixture, testConstructor3);
  FRIEND_TEST(ConwayCellFixture, testCopyConstructor1);
  FRIEND_TEST(ConwayCellFixture, testCopyConstructor2);
  FRIEND_TEST(ConwayCellFixture, testCopyConstructor3);
  FRIEND_TEST(ConwayCellFixture, testEvolve1);
  FRIEND_TEST(ConwayCellFixture, testEvolve2);
  FRIEND_TEST(ConwayCellFixture, testEvolve3);
  FRIEND_TEST(ConwayCellFixture, testClone1);
  FRIEND_TEST(ConwayCellFixture, testClone2);
  FRIEND_TEST(ConwayCellFixture, testClone3);
  FRIEND_TEST(ConwayCellFixture, testCopyAssignment1);
  FRIEND_TEST(ConwayCellFixture, testCopyAssignment2);
  FRIEND_TEST(ConwayCellFixture, testCopyAssignment3);

  FRIEND_TEST(FredkinCellFixture, testConstructor1);
  FRIEND_TEST(FredkinCellFixture, testConstructor2);
  FRIEND_TEST(FredkinCellFixture, testConstructor3);
  FRIEND_TEST(FredkinCellFixture, testCopyConstructor1);
  FRIEND_TEST(FredkinCellFixture, testCopyConstructor2);
  FRIEND_TEST(FredkinCellFixture, testCopyConstructor3);
  FRIEND_TEST(FredkinCellFixture, testEvolve1);
  FRIEND_TEST(FredkinCellFixture, testEvolve2);
  FRIEND_TEST(FredkinCellFixture, testEvolve3);
  FRIEND_TEST(FredkinCellFixture, testClone1);
  FRIEND_TEST(FredkinCellFixture, testClone2);
  FRIEND_TEST(FredkinCellFixture, testClone3);
  FRIEND_TEST(FredkinCellFixture, testCopyAssignment1);
  FRIEND_TEST(FredkinCellFixture, testCopyAssignment2);
  FRIEND_TEST(FredkinCellFixture, testCopyAssignment3);
  /**
   * @brief Whether the cell is alive or not
  */
  bool _alive;
  /**
   * @brief The symbol representation of the cell and its status
  */
  char _symbol;

public:
  /**
   * Constructs an AbstractCell
   * @param alive a bool representing whether the Cell is alive or not
  */
  AbstractCell(bool alive) : _alive(alive), _symbol('/'){};
  /**
   * Increments the value at row, col in neighborCounts if the cell is alive
   * @param neighborCounts a grid containing the count of neighbors that are
   * alive
   * @param row an int representing the row of the cell
   * @param col an int representing the col of the cell
  */
  virtual void flag(vector<vector<int>> &neighborCounts, int row, int col) = 0;
  /**
   * Evolves the cell following the cell's logic
   * @param n an int representing the count of alive neighbors
   * @param pop a reference to an int holding the population count
  */
  virtual bool evolve(int n, int &pop) = 0;
  /**
   * Calculates whether the cell is alive or not, based on the symbol
   * @return a bool representing whether the cell is alive or not
  */
  virtual bool calculateStatus() const = 0;
  /**
   * Creates a clone of the cell
   * @return a pointer of the clone in the heap
  */
  virtual AbstractCell *clone() const = 0;
  /**
   * Destructs the cell
  */
  virtual ~AbstractCell(){};
  /**
   * Prints the cell's symbol to an ostream
   * @param o an ostream to which the symbol is printed
   * @return the ostream
  */
  virtual ostream &print(ostream &o) const = 0;
};

class ConwayCell : public AbstractCell {
  friend ostream &operator<<(ostream &o, const ConwayCell &cc) {
    return cc.print(o);
  }

public:
  ConwayCell(bool alive = false) : AbstractCell(alive) {
    _symbol = _alive ? '*' : '.';
  };

  void flag(vector<vector<int>> &neighborCounts, int row, int col) {
    neighborCounts[row][col] += 1;
  }

  bool evolve(int n, int &pop) {
    if (_alive && (n < 2 || n > 3)) {
      _alive = false;
      _symbol = '.';
    } else if (!_alive && n == 3) {
      _alive = true;
      _symbol = '*';
      ++pop;
    } else if (_alive)
      ++pop;
    return false;
  };

  bool calculateStatus() const {
    if (_symbol == '*')
      return true;
    else
      return false;
  }

  ConwayCell &operator=(const ConwayCell &rhs) {
    _alive = rhs._alive;
    _symbol = rhs._symbol;
    return *this;
  };

  ConwayCell(const FredkinCell &rhs) : AbstractCell(false){};

  AbstractCell *clone() const { return new ConwayCell(*this); };

  ostream &print(ostream &o) const { return o << _symbol; };
};

class FredkinCell : public AbstractCell {
  friend ostream &operator<<(ostream &o, const FredkinCell &fc) {
    return fc.print(o);
  }

private:
  /**
   * @brief The age of the FredkinCell
  */
  int _age;

public:
  FredkinCell(bool alive = false) : AbstractCell(alive), _age(0) {
    _symbol = _alive ? '0' : '-';
  };

  bool evolve(int n, int &pop) {
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
    if (_symbol != '-')
      return true;
    else
      return false;
  }

  void flag(vector<vector<int>> &neighborCounts, int row, int col) { return; }

  FredkinCell(const ConwayCell &rhs) : AbstractCell(false), _age(0){};

  AbstractCell *clone() const { return new FredkinCell(*this); };

  ostream &print(ostream &o) const { return o << _symbol; };
};

class Cell {
private:
  FRIEND_TEST(CellFixture, constructor1);
  FRIEND_TEST(CellFixture, constructor2);
  FRIEND_TEST(CellFixture, constructor3);
  FRIEND_TEST(CellFixture, evolve9);
  AbstractCell *_p;

public:
  /**
   * Constructs the Cell, wrapping nothing (nullptr)
  */
  Cell() : _p(nullptr){};

  /**
   * Constructs a cell wrapping an AbstractCell
   * @param p a pointer to an AbstractCell in the heap
  */
  Cell(AbstractCell *p) : _p(p){};

  /**
   * Constructs a cell wrapping an AbstractCell
   * @param p a reference to an AbstractCell
  */
  Cell(const AbstractCell &rhs) : _p(rhs.clone()){};

  /**
   * Constructs a copy of a Cell
   * @param rhs a constant reference to the Cell to copy
  */
  Cell(const Cell &rhs) : _p(rhs._p == nullptr ? nullptr : rhs._p->clone()){};

  /**
   * Copy-assigns a Cell
   * @param ac a constant reference to the cell to copy
  */
  Cell &operator=(const Cell &ac) {
    delete _p;
    _p = ac._p->clone();
    return *this;
  };

  /**
   * Calculates whether the wrapped cell is alive or not, based on the symbol
   * @return a bool representing whether the cell is alive or not
  */
  bool calculateStatus() const { return _p->calculateStatus(); }

  /**
   * Increments the value at row, col in neighborCounts if the wrapped cell is
   * alive
   * @param neighborCounts a grid containing the count of neighbors that are
   * alive
   * @param row an int representing the row of the cell
   * @param col an int representing the col of the cell
  */
  void flag(vector<vector<int>> &neighborCounts, int row, int col) {
    _p->flag(neighborCounts, row, col);
  }

  /**
   * Evolves the cell following the cell's logic
   * @param n an int representing the count of alive neighbors
   * @param pop a reference to an int holding the population count
  */
  void evolve(int n, int &pop) {
    bool convert = _p->evolve(n, pop);
    if (convert) {
      delete _p;
      _p = new ConwayCell(true);
    }
  }

  /**
   * Destructs the cell and deletes the wrapped cell from the heap
  */
  ~Cell() { delete _p; };

  /**
   * Prints the wrapped cell's symbol to an ostream
   * @param o an ostream to which the symbol is printed
   * @param c the cell to print
   * @return the ostream
  */
  friend ostream &operator<<(ostream &o, const Cell &c) {
    return o << *(c._p);
  };
};

template <typename T> class Life {
private:
  /**
   * @brief The grid holding the cells
  */
  vector<vector<T>> _grid;
  /**
   * @brief The matrix holding the number of alive values for each cell
  */
  vector<vector<int>> _neighborCounts;
  /**
   * @brief The current generation number
  */
  int _generation;
  /**
   * @brief The population count
  */
  int _population;

public:
  /**
   * Constructs a Life instance based on the input stream, the number of rows,
   * and cols
   * @param input an istream cointaining the grid disposition of cells
   * @param rows an int representing the number of rows
   * @param cols an int representing the number of cols
  */
  Life(istream &input, int rows, int cols)
      : _grid(vector<vector<T>>(rows, vector<T>(cols))),
        _neighborCounts(vector<vector<int>>(rows, vector<int>(cols, 0))),
        _generation(0), _population(0) {
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        char t;
        input >> t;

        if (t == '.') {
          _grid[r][c] = T(ConwayCell(false));
        } else if (t == '*') {
          _grid[r][c] = T(ConwayCell(true));
          ++_population;
        } else if (t == '-') {
          _grid[r][c] = T(FredkinCell(false));
        } else {
          _grid[r][c] = T(FredkinCell(true));
          ++_population;
        }
      }
    }
  };

  /**
   * Prints Life's generation, population and grid
   * @param o an ostream to which Life is printed
   * @param l a Life instance to print
   * @return the ostream
  */
  friend ostream &operator<<(ostream &o, const Life &l) {
    o << "Generation = " << l._generation << ", Population = " << l._population
      << "." << endl;
    for (size_t r = 0; r < l._grid.size(); ++r) {
      for (size_t c = 0; c < l._grid[0].size(); ++c) {
        o << l._grid[r][c];
      }
      o << endl;
    }
    return o;
  };

  /**
   * Simulates one run of a generation in the grid
  */
  void simulateGeneration() {
    _population = 0; // resets Population

    // First pass: calculate neighborCounts
    for (int r = 0; r < (int)_grid.size(); ++r) {
      for (int c = 0; c < (int)_grid[0].size(); ++c) {
        if (_grid[r][c].calculateStatus()) {

          if (r - 1 >= 0) // top
            _neighborCounts[r - 1][c] += 1;
          if (c + 1 <= (int)_grid[0].size() - 1) // right
            _neighborCounts[r][c + 1] += 1;
          if (r + 1 <= (int)_grid.size() - 1) // bottom
            _neighborCounts[r + 1][c] += 1;
          if (c - 1 >= 0) // left
            _neighborCounts[r][c - 1] += 1;

          if (r - 1 >= 0 && c - 1 >= 0) // top left
            _grid[r - 1][c - 1].flag(_neighborCounts, r - 1, c - 1);
          if (r - 1 >= 0 && c + 1 <= (int)_grid[0].size() - 1) // top right
            _grid[r - 1][c + 1].flag(_neighborCounts, r - 1, c + 1);
          if (r + 1 <= (int)_grid.size() - 1 &&
              c + 1 <= (int)_grid[0].size() - 1) // bottom right
            _grid[r + 1][c + 1].flag(_neighborCounts, r + 1, c + 1);
          if (r + 1 <= (int)_grid.size() - 1 && c - 1 >= 0) // bottom left
            _grid[r + 1][c - 1].flag(_neighborCounts, r + 1, c - 1);
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
