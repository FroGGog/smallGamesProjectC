#include <iostream>
#include <string>

/// @brief restaring game function
/// @param bool (*func[])(): pointer to a function wich must be called 
/// @return return bool if player still playing game or want to exit
bool RestartGame(bool(*func)()) {
	char userChoice{};
	std::cout << '\n' << "Want to play again? (y/n) : ";
	std::cin >> userChoice;
	if (userChoice == 'y') {
		system("cls");
		func();
	}
	else {
		system("cls");
		return true;
	}
}

/// @brief Prints base game info
/// @param std::string gameName : your game name
/// @param std::string date : date of creation in type of (%D, %M, %Y)
/// @param std::string vesrion : version of your game in type of (X.X.X)
void gameInfo(std::string gameName, std::string date, std::string version = "1.0.0") {
	
	system("cls");
	std::cout << gameName + ". Base version of game vs computer \n";
	std::cout << "Created by Danya Bucenin. \n";
	std::cout << "Version " + version + ". Creation started on " + date + "\n";
	std::cout << "\n";
}

/// @brief Games based menu 
/// @param bool (*functions[])(): takes array of games functions
/// @return return bool if player still playing games or want to exit
bool gamesMenu(bool(*funcions[])()) {
	char userInput{};
	std::string games[]{ "Word Jumble", "Guess My Number", "Hangman", "Tic Tac Toe"};
	bool inGame{};
	std::cout << "Games menu. On 24.10.2023 there are only " << size(games) << " games\n";
	for (short game{}; game < std::size(games); game++) {
		std:: cout << game + 1 << '.' << games[game] << '\n';
	}
	std::cout << "Type from 1-" << size(games) << " to select game(\"q\" for exit) : ";
	std::cin >> userInput;
	switch (userInput) {
	case '1':
		gameInfo("Word Jumble", "20.10.2023");
		inGame = funcions[0]();
		break;
	case '2':
		gameInfo("Guess My Number", "17.10.2023");
		inGame = funcions[1]();
		break;
	case '3':
		gameInfo("Hangman", "24.10.2023");
		inGame = funcions[2]();
		break;
	case '4':
		gameInfo("Tic Tac Toe", "27.10.2023");
		inGame = funcions[3]();
		break;
	case 'q':
		break;
	default:
		std::cout << "Invalide number \n";
		break;
	}
	return inGame;
}