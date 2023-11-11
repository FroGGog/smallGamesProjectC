#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "../../Headers/functions.h"	

/*
Created by Danya Bucenin
Version 1.0.0
Creation started on 20.10.2023
*/


/// @brief shuffels chars in choosen word
/// @param std::string gameWord : choosen game word
void mixWord(std::string gameWord) {
	char tempChar{};
	for (auto shuffleAmount{ rand() % 25 }; shuffleAmount > 0; shuffleAmount--) {
		//choose first char in main word
		auto firstCharIndex{ rand() % gameWord.length() };
		//choose second char in main word
		auto secondCharIndex{ rand() % gameWord.length() };
		tempChar = gameWord[firstCharIndex];
		gameWord[firstCharIndex] = gameWord[secondCharIndex];
		gameWord[secondCharIndex] = tempChar;
	}
	std::cout << "The word is : " + gameWord + '\n';
}

/// @brief get user guess
/// @param bool std::string& userInput : users inputs
void getUserInput(std::string& userInput) {
	std::cout << "Write your word : ";
	std::cin >> userInput;
	std::cout << "\n";
}

/// @brief WordJumble main game function
/// @return return bool if player still playin game or want to exit
bool WordJumbleGame() {
	bool inGame = true;
	srand(time(NULL));
	std::cout << "The bot has selected a word and mixed the letters in it, enter the original word \n";
	std::vector<std::string> gameWords{ "catch", "chair", "crash", "crime", "nasty", "mouse", "drive",
	"input", "blood", "guide", "crowd" };
	//choose game word from vector of words
	std::string gameWord{ gameWords[rand() % gameWords.size()] };
	mixWord(gameWord);
	std::string userInput{};
	unsigned counter{ 1 };
	while (userInput != gameWord) {
		getUserInput(userInput);
		if (userInput == gameWord) {
			std::cout << "Congrats! You won. You spend " + std::to_string(counter) + " attempts";
			inGame = RestartGame(WordJumbleGame);
			return inGame;
		}
		else {
			counter++;
		}
	}
}




