#pragma once

//games functions

/// @brief GuessMyNumber main game function.
/// @return return bool if player still playin game or want to exit
bool GuessMyNumberGame();

/// @brief WordJumble main game function
/// @return return bool if player still playin game or want to exit
bool WordJumbleGame();

/// @brief WordJumble main game function
/// @return return bool if player still playin game or want to exit
bool Hangman();


bool TicTacToe();


//suppoty functions

/// @brief restaring game function
/// @param bool (*func[])(): pointer to a function wich must be called 
/// @return return bool if player still playing game or want to exit
bool RestartGame(bool(*)());
/// @brief Prints base game info
/// @param std::string gameName : your game name
/// @param std::string date : date of creation in type of (%D, %M, %Y)
/// @param std::string vesrion : version of your game in type of (X.X.X)
void gameInfo(std::string, std::string, std::string = "1.0.0");
/// @brief Games based menu 
/// @param bool (*functions[])(): takes array of games functions
/// @return return bool if player still playing games or want to exit
bool gamesMenu(bool(*[])());