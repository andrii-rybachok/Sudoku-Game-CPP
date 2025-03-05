#pragma once
#include <iostream>

struct MainArgs {
    int seed = 1; //seed for randomization
    int gamesize = 9; // size of board
    int nobs = 10; // number of prefield spaces
    int sim = 0; // number of simulation runs 
    bool verbose = false; // flag to print each simulation result for speed tests
    string method;
};