
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "game.hpp"
#include "tests.hpp"
#include "main.hpp"
using namespace std;

int main(int argc, char* argv[]) {

    MainArgs mainArgs;

   
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--seed") ||
            (std::string(argv[i]) == "-s")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> mainArgs.seed))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--seed option requires one argument."
                    << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--gamesize") ||
            (std::string(argv[i]) == "-g")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> mainArgs.gamesize))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--gamesize option requires one argument."
                    << std::endl;
                return 1;
            }
        }
        if ((std::string(argv[i]) == "--Unittest") ||
            (std::string(argv[i]) == "-u")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> mainArgs.sim))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--Unittest option requires one argument."
                    << std::endl;
                return 1;
            }
        }
        if ((std::string(argv[i]) == "--Verbose") ||
            (std::string(argv[i]) == "-v")) {
            mainArgs.verbose = true;
        }
        if ((std::string(argv[i]) == "--nobs") ||
            (std::string(argv[i]) == "-n")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> mainArgs.nobs))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--nobs option requires one argument."
                    << std::endl;
                return 1;
            }
        }
        if ((std::string(argv[i]) == "--RP") ||
            (std::string(argv[i]) == "-rp")) {
            mainArgs.method = "RP";
        }


       
    }

    srand(mainArgs.seed); 


    cout << "-------------------------------------------" << endl;
    cout << "---------------- Have  fun! ---------------" << endl;
    cout << "-------------------------------------------" << endl;

    if (mainArgs.sim == 0) {
        playGame(mainArgs.gamesize, mainArgs.nobs);
    }
    else {
        unitTest(mainArgs.gamesize, mainArgs.nobs, mainArgs.sim, mainArgs.verbose);
    }

    return 0;
}

