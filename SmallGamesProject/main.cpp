#include <iostream>
#include "functions.h"

int main() {

	///@brief pointer array on all games functions*/
	bool (*gamesFunction[4])() = { WordJumbleGame, GuessMyNumberGame, Hangman, TicTacToe };

	bool playingGame{ true };
	//main all games menu function
	while (playingGame) {
		playingGame = gamesMenu(gamesFunction);
	}
	return 0;
}