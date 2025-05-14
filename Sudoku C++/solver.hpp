
#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
// board class to hold state of sudoku game
class Board {
    int N;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> immutable;
    std::vector<std::vector<bool>> infeasible;
    std::vector<bool> row; //if number + i can be used
    std::vector<bool> col; // if number + j can be used
    std::vector<bool> square;// if number + (i/3)*3+j/3 can be used
public:

    // To be implemented as matrix with single array
    Board(int _N) : N(_N) {

        //matrix to keep track of values
        grid=std::vector<std::vector<int>>( N, std::vector<int>(N,0) );

        //matrix to track immutables
        immutable = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));

        // matrix to track which values are causing infeasibilitsy
        // these are problem cells that will be
        // highlighted in red during gameplay
        infeasible = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));

        
    }

    void printPuzzle(); // print the puzzle to the screen
    bool checkPuzzle(); // Check if puzzle is complete
    void clearPuzzle(); //Clear mutables from puzzle
    bool inBounds(int val); //Check if value can exist in puzzle
    bool feasibleUser(int row, int col, int val);
    void resetInfeasible();

    bool isSafe(int x, int y, int val) {
        if (!row[val + x] && !col[val + y] && !square[(x / 3) * 3 + y / 3 + grid[x][y]]) {
            return true;
        }
        return false;
    }

    void resetNumberCache() {
        row = std::vector<bool>(N*N, false);
        col = std::vector<bool>(N * N, false);
        square = std::vector<bool>(N * N, false);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j]!=0) {
                    row[grid[i][j]+i] = true;
                    col[grid[i][j] + j] = true;
                    square[(i / 3) * 3 + j / 3+grid[i][j]] = true;
                }
            }
        }
    }
    //Operator overload to check grid value
    int& operator() (int x, int y) {
        assert(x < N && y < N);
        return grid[x][y];
    }

    //assign value to x,y
    void assignValue(int x, int y, int val) {
        (*this)(x, y) = val;

       
    }
    void setNumberCache(int x, int y, int nval, bool val) {
        row[nval + x] = val;
        row[nval + y] = val;
        row[nval + (x / 3) * 3 + y / 3] = val;
    }
    // toggle cell mutability
    void assignImmutable(int x, int y, bool val) {
        immutable[x][y] = val;
    }

    //Checks if cell is ummutable (not changeable by solve/user)
    bool checkImmutable(int x, int y) {
        return immutable[x][y];
    }

    //Keep track of "problem cells"
    //i.e. cells that cause infeasibility
    bool isProblem(int x, int y) {
        return infeasible[x][y];
    }

    //Get size of game
    //ie. 9 for 9x9 game
    int getSize() {
        return N;
    }

    // function for debugging (kind of dumb, but need to change its
    // signature each time you change the puzzle size...but I suppose
    // in practice we will never need this)
    void setFromArray(int a[4][4]) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                grid[i][j] = a[i][j];
    }

};

bool feasible(Board& b, int row, int col, int val);
bool solve(Board& b, int row, int col);
int* genPerm(int N);
Board generatePuzzle(int n, int nobs);
bool solveEucharistic(Board& board);

