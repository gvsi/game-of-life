// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl

#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----------------------
    // Life<ConwayCell> 21x13
    // ----------------------

    cout << "*** Life<ConwayCell> 21x13 ***" << endl;
    /*
    Simulate 12 evolutions.
    Print every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    int rows, cols;
    cin >> rows >> cols;
    Life<ConwayCell> l1(cin, rows, cols);
    for (int i = 0; i <= 12; ++i) {
      cout << l1 << endl;
      l1.simulateGeneration();
    }

    // ----------------------
    // Life<ConwayCell> 20x29
    // ----------------------

    cout << "*** Life<ConwayCell> 20x29 ***" << endl;
    /*
    Simulate 28 evolutions.
    Print every 4th grid (i.e. 0, 4, 8, ... 28)
    */

    cin >> rows >> cols;
    Life<ConwayCell> l2(cin, rows, cols);
    for (int i = 0; i <= 28; ++i) {
      if (i % 4 == 0)
        cout << l2 << endl;
      l2.simulateGeneration();
    }

    // -----------------------
    // Life<ConwayCell> 109x69
    // -----------------------

    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    /*
    Simulate 283 evolutions.
    Print the first 10 grids (i.e. 0, 1, 2, ... 9).
    Print the 283rd grid.
    Simulate 40 evolutions.
    Print the 323rd grid.
    Simulate 2177 evolutions.
    Print the 2500th grid.
    */

    cin >> rows >> cols;
    Life<ConwayCell> l3(cin, rows, cols);
    for (int i = 0; i <= 2500; ++i) {
      if (i < 10 || i == 283 || i == 323 || i == 2500)
        cout << l3 << endl;
      l3.simulateGeneration();
    }

    // -----------------------
    // Life<FredkinCell> 20x20
    // -----------------------

    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */

    cin >> rows >> cols;
    Life<FredkinCell> l4(cin, rows, cols);
    for (int i = 0; i <= 5; ++i) {
      cout << l4 << endl;
      l4.simulateGeneration();
    }

    // ----------------
    // Life<Cell> 20x20
    // ----------------

    cout << "*** Life<Cell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */

    cin >> rows >> cols;
    Life<Cell> l5(cin, rows, cols);
    for (int i = 0; i <= 5; ++i) {
      cout << l5 << endl;
      l5.simulateGeneration();
    }

    return 0;}
