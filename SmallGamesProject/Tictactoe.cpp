#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "functions.h"

/*
Created by Danya Bucenin
Version 1.0.0
Creation started on 27.10.2023
*/


/// @brief print game field
/// @param const char gameField[] : main game field
void printgameField(const char gameField[]) {
	std::cout << '\n';
	//prints gameField's strings
	for (unsigned i{ 0 }; i < 9; i++) {
		std::cout << ' ' << gameField[i] << " ";
		if ((i + 1) % 3 != 0) {
			std::cout << '.';
		}
		if (i != 8 && (i + 1) % 3 == 0) {
			std::cout << '\n';
			//print floors for gameField
			for (unsigned i{ 1 }; i <= 12; i++) {
				std::cout << '.';
			}
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}

/// @brief ask if player want to play as X or as O
/// @param char& userChar : game user main char
/// @param char& botsChar : game bots main char
void chooseTurn(char& userChar, char& botsChar) {
	std::cout << "\nDo you want to start (play as X) or bot will start?(type f/s)\n";
	std::string userChoice{};
	std::cin >> userChoice;
	//checks if user wrote letter
	if (isalpha(userChoice[0]) == 0) {
		std::cout << "Please write f or s. Where f is first and s is second\n";
		chooseTurn(userChar, botsChar);
	}
	//checks if user wrote only one letter
	else if (userChoice.length() > 1) {
		std::cout << "Please write f or s. Where f is first and s is second\n";
		chooseTurn(userChar, botsChar);
	}
	else if (userChoice[0] != 'f' && userChoice[0] != 's') {
		std::cout << "Please enter f or s.\n";
		chooseTurn(userChar, botsChar);
	}
	//user firt turn
	if (userChoice == "f") {
		userChar = 'X';
		botsChar = 'O';
	}
	//user goes second
	else {
		userChar = 'O';
		botsChar = 'X';
	}
}

/// @brief function that proceeds player turn
/// @param char& userChar : game user main char
/// @param char gameField[] : main game field
void playerTurn(char& userChar, char gameField[]) {
	std::cout << "\nPlease choose your position from 1-9 : ";
	//its unsigned so if user print negative num it will not be negative
	unsigned userPos{};
	std::cin >> userPos;
	std::cout << '\n';
	//checks if user wrote pos larger than 9
	if (userPos > 9 || userPos == 0) {
		std::cout << "Choose postion from 1-9.\n";
		playerTurn(userChar, gameField);
	}
	//check if user wrote num not letter
	else if (isdigit(userPos) != 0) {
		std::cout << "Please enter number from 1-9.\n";
		playerTurn(userChar, gameField);
	}
	//check if place is empty and set new char on it
	if (gameField[userPos-1] == ' ') {
		gameField[userPos-1] = userChar;
	}
	else {
		std::cout << "This place if occupied. Choose another one.\n";
		playerTurn(userChar, gameField);
	}
}

/// @brief checks if some on won on any raw
/// @param char gameField[] : main game field
/// @return int : if someone won return 1, else 0
int checkRows(char gameField[]) {
	for (unsigned i{ 0 }; i < 9;) {
		if (gameField[i] == gameField[i + 1] && gameField[i] != ' ') {
			if (gameField[i + 1] == gameField[i + 2]) {
				return 1;
			}
			else {
				i += 3;
			}
		}
		else {
			i += 3;
		}
	}
	return 0;
}

/// @brief checks if some on won on any column
/// @param char gameField[] : main game field
/// @return int : if someone won return 1, else 0
int checkColumns(char gameField[]) {
	for (unsigned i{ 0 }; i <= 2;) {
		if (gameField[i] == gameField[i + 3] && gameField[i] != ' ') {
			if (gameField[i] == gameField[i + 6]) {
				return 1;
			}
			else {
				i++;
			}
		}
		else {
			i++;
		}
	}
	return 0;
}

/// @brief checks if some on won on any diagonal
/// @param char gameField[] : main game field
/// @return int : if someone won return 1, else 0
int checkDiagonals(char gameField[]) {
	if (gameField[0] == gameField[4] && gameField[0] != ' ') {
		if (gameField[0] == gameField[8]) {
			return 1;
		}
	}
	if(gameField[2] == gameField[4] && gameField[2] != ' ') {
		if (gameField[2] == gameField[6]) {
			return 1;
		}
	}
	return 0;
}

/// @brief main check function that calls every checking function
/// @param char gameField[] : main game field
/// @return int : 1 someone won, 0 noone
int checkWinner(char gameField[]) {
	short totalScore{};
	totalScore += checkRows(gameField);
	totalScore += checkColumns(gameField);
	totalScore += checkDiagonals(gameField);
	//if any of these functions return more that 0, that means that someone won
	if (totalScore > 0) {
		return 1;
	}
	else {
		return 0;
	}

}
//third param true if for player, false for bot

/// @brief function that check if player of bots can win in one turn
/// @param char gameField[] : main game field
/// @param char& playerChar : main player game char
/// @param char& botChar : main bot game char
/// @param bool playerOrBot : if checking for player is true, for bot is false
/// @return short : index of posstiton, or -1 if no posstion for one turn win
short checkWinOneTurn(char gameField[], char& playerChar, char& botChar , bool playerOrBot) {
	//set char for checking 
	char localGameCheckChar{};
	if (playerOrBot) {
		localGameCheckChar = playerChar;
	}
	else {
		localGameCheckChar = botChar;
	}
	//copy to another array so we can check each turn
	char copyGameField[9]{};
	for (short i{}; i < 9; i++ ) {
		copyGameField[i] = gameField[i];
	}
	short totalScore{};
	//check each turn and trying to find winning one
	for (short i{}; i < 9; i++) {
		if (copyGameField[i] != ' ') {
			continue;
		}
		copyGameField[i] = localGameCheckChar;
		//if returns non zero value that means that someone can win
		totalScore += checkWinner(copyGameField);
		if (totalScore > 0) {
			return i;
		}
		copyGameField[i] = ' ';
	}
	return -1;
}

/// @brief function that check all possible bots moves
/// @param char gameField[] : main game field
/// @param char& playerChar : player game char
/// @param char&botsChar : bots game char
void searchAllMoves(char gameField[], char& playerChar, char& botsChar) {
	int oneMoveWinPos{ -1 };
	std::vector<int> possibleMoves{};
	for (short i{}; i < 9; i++) {
		//if space if not empty we cant place here
		if (gameField[i] != ' ') {
			possibleMoves.push_back(0);
			continue;
		}
		//if center is empty this will be best move
		else if (i == 4 && gameField[i] == ' ') {
			possibleMoves.push_back(3);
		}
		//side spaces not corners
		else if (i % 2 != 0) {
			possibleMoves.push_back(1);
			continue;
		}
		//corners are better than side spaces
		else if (i % 2 == 0) {
			possibleMoves.push_back(2);
		}
	}
	//check if bot can win in one turn
	oneMoveWinPos = checkWinOneTurn(gameField, playerChar, botsChar, false);
	if (oneMoveWinPos >= 0) {
		gameField[oneMoveWinPos] = botsChar;
		return;
	}
	//check if player can win in one turn
	oneMoveWinPos = checkWinOneTurn(gameField, playerChar, botsChar, true);
	if (oneMoveWinPos >= 0) {
		gameField[oneMoveWinPos] = botsChar;
		return;
	}
	//if no possible one turn wins, do best move
	if(oneMoveWinPos < 0){
		auto maxElem = std::max_element(possibleMoves.begin(), possibleMoves.end());
		auto foundedMaxIndex = find(possibleMoves.begin(), possibleMoves.end(), *maxElem) - possibleMoves.begin();
		gameField[foundedMaxIndex] = botsChar;
		return;
	}
	
}

bool checkDraw(char gameField[]) {
	std::vector<char> copyVector{};
	for (short i{}; i < 9; i++) {
		copyVector.push_back(gameField[i]);
	}
	//if there are no empty spaces in game field that is draw
	auto findEmptyChar = find(copyVector.begin(), copyVector.end(), ' ');
	if (findEmptyChar != std::end(copyVector)) {
		return false;
	}
	else {
		return true;
	}
}

/// @brief main bot turn function
/// @param char gameField[] : main game field
/// @param char&botsChar : main game bots char
void botsTurn(char& botsChar, char gameField[], char& userChar) {
	std::cout << "\n Now its bots turn! \n";
	//if bot goes first and center is empty place in center
	if (botsChar == 'X' && gameField[4] == ' ') {
		gameField[4] = botsChar;
		return;
	}
	searchAllMoves(gameField, userChar, botsChar);

}

/// @brief main TicTacToe function
/// @return bool : check if player stil playing game or not
bool TicTacToe() {
	bool inGame{ true };
	std::cout << "Positions : 1-9. Rows starts with 1,4,7\n";
	//main game gameField
	char gameField[9]{
		' ',' ',' ',
		' ',' ',' ',
		' ',' ',' '
	};
	char userChar{};
	char botsChar{};
	printgameField(gameField);
	chooseTurn(userChar, botsChar);
	while (inGame) {
		//situation where player goes first
		if (userChar == 'X') {
			playerTurn(userChar, gameField);
			printgameField(gameField);
			if (checkDraw(gameField)) {
				std::cout << "\nThat time its draw!\n";
				inGame = false;
				continue;
			}
			if (checkWinner(gameField) == 1) {
				std::cout << "\nX is winner!\n";
				inGame = false;
				continue;
			}
			botsTurn(botsChar, gameField, userChar);
		}
		//situation where bot goes first
		else {
			botsTurn(botsChar, gameField, userChar);
			printgameField(gameField);
			if (checkDraw(gameField)) {
				std::cout << "\nThat time its draw!\n";
				inGame = false;
				continue;
			}
			if (checkWinner(gameField) == 1) {
				std::cout << "\nX is winner!\n";
				inGame = false;
				continue;
			}
			playerTurn(userChar, gameField);

		}
		printgameField(gameField);
		if (checkDraw(gameField)) {
			std::cout << "\nThat time its draw!\n";
			inGame = false;
			continue;
		}
		if (checkWinner(gameField) == 1) {
			std::cout << "\nO is winner!\n";
			inGame = false;
		}

	}

	inGame = RestartGame(Hangman);
	return inGame;

}