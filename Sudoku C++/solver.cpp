

#include "solver.hpp"
#include <iostream>
#include <cassert>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to print the board
void Board::printPuzzle() {

    int blockSize = (int)sqrt(N);
    int extra_space = N / 10;

    for (int i = 0; i < N; i++) {
        cout << "+---";
        for (int j = 0; j < extra_space; j++)
            cout << "-";
    }

    cout << "+" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| ";
        for (int j = 0; j < N; j++) {

            if ((*this)(i, j) == 0) {
                cout << ".";
                for (int k = 0; k < extra_space; k++)
                    cout << " ";
            }
            else {
                if (!isProblem(i, j)) {
                    cout << (*this)(i, j);
                }
                else {
                    cout << "\033[31m" << (*this)(i, j) << "\033[39m";
                }

                int numDigits = (*this)(i, j) / 10;
                while (numDigits < extra_space) {
                    cout << " ";
                    numDigits++;
                }

            }

            if ((j + 1) % blockSize == 0) {
                cout << " | ";
            }
            else {
                cout << "   ";
            }
        }

        cout << endl;
        if ((i + 1) % blockSize == 0) {
            for (int j = 0; j < N; j++) {
                cout << "+---";

                for (int k = 0; k < extra_space; k++)
                    cout << "-";
            }

            cout << "+" << endl;
        }

    }

}


// Check if the puzzle is complete
bool Board::checkPuzzle() {
    int val = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            val = (*this)(i, j);
            (*this)(i, j) = 0;
            if (!feasible(*this, i, j, val)) {
                (*this)(i, j) = val;
                return false;
            }
            (*this)(i, j) = val;
        }
    return true;
}

//Empty all cells that are not immutable
// immutable = prefilled by the randomly generated puzzle
void Board::clearPuzzle() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!checkImmutable(i, j))
                (*this)(i, j) = 0;
}


//Checks if is in good range
bool Board::inBounds(int val) {
    if ((val > 0) && (val <= N)) {
        return true;
    }
    else {
        return false;
    }
}


void Board::resetInfeasible() {
    // Assuming N is the size of the board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            infeasible[i][j] = false;  // Set each element to false
        }
    }
}
//Checks for feasibility of the board
bool Board::feasibleUser(int row, int col, int val) {

    int blockSize = (int)sqrt(N);
    if (!inBounds(row+1)||!inBounds(col+1)) {
        return false;
    }


    resetInfeasible();
    // Check if value already exists in the row
    for (int i = 0; i < N; i++) {
        if ((*this)(row, i) == val) {
            infeasible[row][i] = true;
            return false;  // Value already in the same row
        }
    }

    // Check if value already exists in the column
    for (int i = 0; i < N; i++) {
        if ((*this)(i, col) == val) {
            infeasible[col][i] = true;
            return false;  // Value already in the same column
        }
    }

    // Check if value already exists in the 3x3 block
    int blockRowStart = (row / blockSize) * blockSize;
    int blockColStart = (col / blockSize) * blockSize;

    for (int i = blockRowStart; i < blockRowStart + blockSize; i++) {
        for (int j = blockColStart; j < blockColStart + blockSize; j++) {
            if ((*this)(i, j) == val) {
                infeasible[i][j] = true;
                return false;  // Value already in the same 3x3 block
            }
        }
    }
    return true;
}

// Helper function for solve: checks to see if candidate is feasible or not
bool feasible(Board& board, int row, int col, int val) {
    int N = board.getSize();
    assert(row < N);
    assert(col < N);
    int blockSize = (int)sqrt(N);

    // See if used yet in row
    for (int j = 0; j < N; j++)
        if (board(row, j) == val) return false;

    // See if used yet in col
    for (int i = 0; i < N; i++)
        if (board(i, col) == val) return false;

    // coordinates of upper-left hand corner of block that (row,col) occupies
    int blockRow = blockSize * (row / blockSize);
    int blockCol = blockSize * (col / blockSize);

    // See if used yet in block
    for (int i = 0; i < blockSize; i++)
        for (int j = 0; j < blockSize; j++)
            if (board(blockRow + i, blockCol + j) == val)
                return false;

    return true;
}

bool solveEucharisticRec(Board& board,int row, int col) {

    int n = board.getSize();
    assert(n == pow(sqrt(n), 2));

    if (row == n - 1 && col== n)
        return true;
    if (col == n) {
        row++;
        col = 0;
    }
    if (board(row, col) != 0) {
        return solveEucharisticRec(board, row, col + 1);
    }

    for (int num = 1; num <= n; n++) {
        if (board.isSafe(row, col, num)) {
            board.assignValue(row, col, num);
            board.setNumberCache(row, col, num, true);

            if (solveEucharisticRec(board, row, col + 1)) {
                return true;
            }

            board.setNumberCache(row, col, num, false);
        }
    }
    return false;
}

bool solveEucharistic(Board& board) {
    board.resetNumberCache();
    return solveEucharisticRec(board,0,0);
}

bool solve(Board& board, int row, int col) {
    // N: size of the board; note N must be a perfect square!
    int N = board.getSize();
    assert(N == pow(sqrt(N), 2));

    // Check to see if we are at end of board
    if (row == N)
        return true;

    // Skip over values that have been filled in
    if (board(row, col) != 0) {
        if (col == (N - 1)) {
            if (solve(board, row + 1, 0)) return true;
        }
        else {
            if (solve(board, row, col + 1)) return true;
        }
        return false;
    }

    // Try different values
    for (int val = 1; val <= N; val++) {
        if (feasible(board, row, col, val)) {
            board(row, col) = val;
            if (col == (N - 1)) {
                if (solve(board, row + 1, 0)) return true;
            }
            else {
                if (solve(board, row, col + 1)) return true;
            }
        }
    }

    // We failed to find a value that works, so backtrack
    board(row, col) = 0;
    return false;
}



Board generatePuzzle(int N, int nobs) {
    // generate permutation of 1...n
    // fill diagonal of board with this permutation
    // solve board
    // randomly remove enough entries to only leave nobs observed
    assert(nobs <= N * N);
    Board board(N);

    int* perm = genPerm(N); // permuted 1...N

    // fill diag of board with perm
    for (int i = 0; i < N; i++)
        board(i, i) = perm[i];
    delete[] perm;

    // solve board
    bool isSolved = solve(board, 0, 0);
    assert(isSolved); // by filling diagonal, this should never be violated

    // remove N*N - nobs entries
    perm = genPerm(N * N);
    int x, y;
    for (int i = 0; i < (N * N - nobs); i++) {
        x = (perm[i] - 1) / N;
        y = (perm[i] - 1) % N;
        board(x, y) = 0;
        board.assignImmutable(x, y, false);
    }

    delete[] perm;
    return board;

}


int* genPerm(int N) {

    // initialize array [1,...,N]
    int* x = new int[N];
    for (int i = 0; i < N; i++)
        x[i] = i + 1;

    // generate random permutation of [1,...,N]
    int rindex;
    int temp;
    for (int i = (N - 1); i > 0; i--) {
        rindex = rand() % (i + 1);
        temp = x[i];
        x[i] = x[rindex];
        x[rindex] = temp;
    }

    return x;

}
