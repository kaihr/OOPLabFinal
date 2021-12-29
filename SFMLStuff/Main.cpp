#include <SFML/Graphics.hpp>

#include "ChessGame.h"
#include "TextureManager.h"

#include <iostream>

TextureManager *TextureManager::instance = NULL;

int main()
{
	ChessGame game;
	game.run();

	return 0;
}