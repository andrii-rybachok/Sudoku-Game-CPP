
#include "game.hpp"
#include "tests.hpp"
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std::chrono;
using namespace std;

void unitTest(int size, int nobs, int ntimes, bool verbose) {

    int total = 0;
    int total2 = 0;

    for (int i = 0; i < ntimes; ++i)
    {
        Board board = generatePuzzle(size, nobs);


        auto t = measure<nanoseconds>::execution(solve,
            board, 0, 0);
        auto t2 = measure<nanoseconds>::execution(solveEucharistic, board);

        if (verbose)
            cout << "Backtrace solved in " << t << " ns." << \
            " Candidate Reduction strategy solved in " << t2 << " ns." << endl;

        total += t;
        total2 += t2;
    }

    cout << "\n Average time for Backtrace: " << total / ntimes <<" ns" << endl;
    cout << "Average time for Candidate Reduction strategy: " << total2 / ntimes <<" ns" << endl;

}