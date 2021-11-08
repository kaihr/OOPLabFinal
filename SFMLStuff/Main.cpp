#include <SFML/Graphics.hpp>
#include <iostream>
#include "ChessGame.h"

int main()
{
	ChessGame game;
	game.run();

	std::cout << "FOO BAR" << std::endl;

	return 0;
}