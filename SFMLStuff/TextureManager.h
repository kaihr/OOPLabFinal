#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

class TextureManager {
public:
	static TextureManager *instance;

private:
	sf::Texture _arr[PIECES::N_TEXTURES];

private:
	TextureManager() {};
	TextureManager(const TextureManager& other) {};

public:
	static TextureManager *getInstance() {
		if (!instance) {
			instance = new TextureManager;

			instance->_arr[WHITE_BISHOP].loadFromFile("Assets\\white_bishop.png");
			instance->_arr[WHITE_KING].loadFromFile("Assets\\white_king.png");
			instance->_arr[WHITE_KNIGHT].loadFromFile("Assets\\white_knight.png");
			instance->_arr[WHITE_PAWN].loadFromFile("Assets\\white_pawn.png");
			instance->_arr[WHITE_QUEEN].loadFromFile("Assets\\white_queen.png");
			instance->_arr[WHITE_ROOK].loadFromFile("Assets\\white_rook.png");

			instance->_arr[BLACK_BISHOP].loadFromFile("Assets\\black_bishop.png");
			instance->_arr[BLACK_KING].loadFromFile("Assets\\black_king.png");
			instance->_arr[BLACK_KNIGHT].loadFromFile("Assets\\black_knight.png");
			instance->_arr[BLACK_PAWN].loadFromFile("Assets\\black_pawn.png");
			instance->_arr[BLACK_QUEEN].loadFromFile("Assets\\black_queen.png");
			instance->_arr[BLACK_ROOK].loadFromFile("Assets\\black_rook.png");
		}

		return instance;
	}

	static sf::Texture getTexture(PIECES id) {
		return getInstance()->_arr[id];
	}
};