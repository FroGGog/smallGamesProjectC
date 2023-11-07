#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "functions.h";


/*
Created by Danya Bucenin
Version 1.0.0
Creation started on 20.10.2023
*/


/// @brief get and check user input
/// @param std::string& userChar : string with user input
void GetUserChar(std::string& userChar) {
	std::cout << "\nWrite letter: ";
	std::cin >> userChar;
	if (isalpha(userChar[0]) == 0) {
		std::cout << "Write alphabet letter please!\n";
		GetUserChar(userChar);
	}
	else if (userChar.length() > 1) {
		std::cout << "Write one letter please! \n";
		GetUserChar(userChar);
	}
}

/// @brief checkin if user already used letter or not
/// @param std::vector<char>& usedLetters : vector with all letters used in game
/// @param char& userChar : user input
/// @return bool : (true) - if added new letter, (false) - if letter already in vector
bool checkIfCharInUsedLetters(std::vector<char>& usedLetters, char& userChar) {
	auto result = find(begin(usedLetters), end(usedLetters), userChar) - begin(usedLetters);
	if (result == usedLetters.size()) {
		usedLetters.push_back(userChar);
		return true;
	}
	else {
		std::cout << userChar <<  " is already used \n";
		return false;
	}
}

/// @brief check and open letters in word
/// @param std::string& gameWord : main game word
/// @param std::vector<char>& gameField : field on wich you want to open and check letters
/// @param char& userChar : user input 
bool openLetters(std::string& gameWord, std::vector<char>& gameField, char& userChar) {

	auto indexInWord{ find(begin(gameWord), end(gameWord), userChar) - begin(gameWord) };
	if (indexInWord == gameWord.size()) {
		std::cout << "No such letter in word\n";
		return false;
	}
	while (indexInWord < gameWord.size()) {
		indexInWord = find(begin(gameWord) + indexInWord, end(gameWord), userChar) - begin(gameWord);
		if (indexInWord == gameWord.size()) {
			return true;
		}
		gameField[indexInWord] = userChar;
		indexInWord++;
	}
	std::cout << "\nFound such letter \n";
	return true;
}

/// @brief prints game field
/// @param std::vector<char>& gameField : main game field with opened and closed letters
/// 
void printGameField(std::vector<char>& gameField) {
	for (auto i : gameField) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

/// @brief main Hangman function
/// @return bool : check if player stil playing game or not
bool Hangman() {
	bool inGame{ true };
	srand(time(NULL));
	std::vector<std::string> gameWords{ "cat","dog","hat", "unicorn", "octopus", "abracadabra", "table", "chair", "bicycle"};

	std::string gameWord{ gameWords[rand() % gameWords.size()] };
	//game field consist of _
	std::vector<char> gameField(gameWord.size(), '_');
	//vector for used letters
	std::vector<char> usedLetters{};

	std::string userString = " ";
	char userChar = ' ';
	short attempts{ 8 };

	while (attempts > 0) {
		printGameField(gameField);
		std::cout << "\nYou have " << attempts << " attempts left\n";
		GetUserChar(userString);
		userChar = userString[0];
		//checks if user tryies to enter same letter again
		if (!checkIfCharInUsedLetters(usedLetters, userChar)) {
			continue;
		}
		
		if (!openLetters(gameWord, gameField, userChar)) {
			attempts--;
		}

		//check if user already won
		auto checkWin = find(begin(gameField), end(gameField), '_') - begin(gameField);
		if (checkWin == gameField.size()) {
			printGameField(gameField);
			std::cout << "\nCongrats! You win!\n";
			attempts = 2;
			break;
		}
	}
	if (attempts < 1) {
		std::cout << "You lose. The word was - " + gameWord;
	}
	
	inGame = RestartGame(Hangman);
	return inGame;
}