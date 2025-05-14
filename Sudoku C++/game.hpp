
#pragma once
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
//#include "altproj.hpp"


struct UserInput {
	int user_inputs[3];
	int getCol() {
		return user_inputs[0] - 1;
	}
	int getRow() {
		return user_inputs[1] - 1;
	}
	int getNumber() {
		return user_inputs[2];
	}
	
};
//main function to run the user interactive game
void playGame(int size, int nobs);
// helper function to prompt user to play again
void playAgainPrompt(int size, int nobs);

