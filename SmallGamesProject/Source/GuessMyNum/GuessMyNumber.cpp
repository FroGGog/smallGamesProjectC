#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../../Headers/functions.h"

/*
Created by Danya Bucenin
Version 1.0.0
Creation started on 17.10.2023
*/

/// @brief function that check users inputs
/// @param short mainNumber : main game number
/// @param short userNumber : number that user input
/// @return return bool : if user corret 0, if user wrong 1
short getAndCheckUserNumber(short mainNumber, short userNumber) {
	std::cout << '\n';
	if (mainNumber > userNumber) {
		std::cout << "Main number is greater than yours \n";
		return 1;
	}
	else if (mainNumber < userNumber) {
		std::cout << "Main number is lower than your \n";
		return 1;
	}
	else {
		std::cout << "That's correct! \n";
		return 0;
	}
}

/// @brief GuessMyNumber main game function
/// @return return bool if player still playin game or want to exit
bool GuessMyNumberGame() {
	std::cout << "The bot chose a number between 0 and 100. Try to guess the number \n";
	bool inGame = true;
	srand(time(NULL));
	//computer number
	short guessNum{ rand() % 100 };
	//amount of user attempts
	short attempts{};
	short userInput{};
	while (userInput != guessNum) {
		std::cout << "Write number between 0 and 100 : ";
		std::cin >> userInput;
		attempts += getAndCheckUserNumber(guessNum, userInput);
		std::cout << "Attempts : " << attempts << '\n';
	}
	std::cout << "You spend " << attempts << " attempts" << '\n';
	inGame = RestartGame(GuessMyNumberGame);
	return inGame;
}