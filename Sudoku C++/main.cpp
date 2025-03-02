
#include <iostream>
#include <regex>
#include <sstream>

#include "game.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    int seed=1; //random seed
    int gamesize = 9; // default size of game
    int nobs = 10; // default number of prefilled spaces

    // Handle command line args
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--seed") ||
            (std::string(argv[i]) == "-s")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> seed))
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
                if (!(ss >> gamesize))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--gamesize option requires one argument."
                    << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--nobs") ||
            (std::string(argv[i]) == "-n")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> nobs))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else {
                std::cerr << "--nobs option requires one argument."
                    << std::endl;
                return 1;
            }
        }



       
    }

    srand(seed); // set random seed

    // Welcome message
    cout << "-------------------------------------------" << endl;
    cout << "---------------- Have  fun! ---------------" << endl;
    cout << "-------------------------------------------" << endl;


    playGame(gamesize, nobs);


    return 0;
}

