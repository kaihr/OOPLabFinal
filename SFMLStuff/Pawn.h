#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"
#include "TextureManager.h"

class Pawn : public Piece {
private:
	int _positiveDirection;

	sf::Texture _texture;

public:
	Pawn(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite)
	{	
		_positiveDirection = -1; // White piece move from the bottom row to the top row
		if (!isWhite)
			_positiveDirection = 1;

		if (_isWhite)
			_texture = TextureManager::getTexture(PIECES::WHITE_PAWN);
		else
			_texture = TextureManager::getTexture(PIECES::BLACK_PAWN);

		_sprite.setTexture(_texture);
		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]);

	virtual Piece* handleInput(const sf::Event& event, Piece* pieces[BOARD_SIZE][BOARD_SIZE]);
};
