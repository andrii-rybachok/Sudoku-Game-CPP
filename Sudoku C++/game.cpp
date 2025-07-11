
#include <iostream>
#include <regex>
#include <sstream>
#include "game.hpp"
#include "solver.hpp"
using namespace std;

void playGame(int size, int nobs);


//play game again
void playAgainPrompt(int size, int nobs) {
    string user_response;

    do {
        cout << "Play again? y/n" << endl;
        getline(cin, user_response);
    } while ((user_response != "y") && (user_response != "n"));

    if (user_response == "y") {
        playGame(size, nobs);
    }
    else {
        return;
    }
}

void playGame(int size, int nobs) {

    string user_entry;
    bool solverSucces = false;
    Board board = generatePuzzle(size, nobs);
    regex rgx("[0-9]{1,}"); // For parsing user input
    smatch match;

    unique_ptr<UserInput> input= make_unique<UserInput>();
    // Repeat until puzzle is solved
    do {


        board.printPuzzle(); // print puzzle
        cout << "\nEnter column, row and the value:";

        getline(cin, user_entry); // get user input


        if (user_entry == "s" || user_entry == "Solve" || user_entry=="solve") {
            solverSucces = solve(board, 0, 0);
            board.printPuzzle();
            break;
        }else if (user_entry == "c" || user_entry == "Clear" || user_entry=="clear") {
            board.clearPuzzle();
            continue;
        }

        // Assuming no special command, attempt to parse user input
        int count = 0;
        
        for (sregex_iterator i = sregex_iterator(user_entry.begin(),
            user_entry.end(), rgx);
            i != sregex_iterator();
            ++i)
        {
            smatch m = *i;
            input->user_inputs[count] = stoi(m.str());
            ++count;
        }


        // If parse values are out of range... throw error and continue
        for (int i = 0; i < 3; i++) {
            if (!board.inBounds(input->user_inputs[i])) {
                cout << "Values entered must be between 1 and " << board.getSize() << endl;
                continue;
            }
        }


        // Assign board value if feasible move

        if (board.feasibleUser(input->getCol(), input->getRow(), input->getNumber()) == true) {

            if (board.checkImmutable(input->getCol(), input->getRow()) == false) {
                board.assignValue(input->getCol(), input->getRow(), input->getNumber());

            }
            else {
                cout << "You can't change that value!" << endl;
            }

        }
        else {
            cout << "Not feasible!" << endl;
        }

        // reset inputs to 0, will cause invalid message if unchanged on next round
        for (int i = 0; i < 3; i++) {
           input->user_inputs[i] = 0;
        }

    } while (!board.checkPuzzle());

    string user_response;

    if (solverSucces) {

        cout << "Well done, the puzzle is solved!" << endl;
        playAgainPrompt(size, nobs);

    }
    else {

        cout << "Could not solve puzzle based on pre-filled values" << endl;

        do {

            cout << "Would you like to clear and try to solve? y/n" << endl;
            getline(cin, user_response);

        } while ((user_response != "y") && (user_response != "n"));

        if (user_response == "y") {
            board.clearPuzzle();
            solveEucharistic(board);
            board.printPuzzle();
            playAgainPrompt(size, nobs);
        }

    }


}
