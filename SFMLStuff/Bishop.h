#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class Bishop : public Piece {
private:
	sf::Texture _texture;
public:
	Bishop(int row = 0, int col = 0, bool isWhite = true)
	{
		_row = row;
		_col = col;
		_isWhite = isWhite;

		if (_isWhite)
			_texture.loadFromFile("Assets\\white_bishop.png");
		else
			_texture.loadFromFile("Assets\\black_bishop.png");


		_sprite.setTexture(_texture);

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		if (!(abs(nextRow - _row) == abs(nextCol - _col)))
			return false;
		if (nextRow > _row)
		{
			if (nextCol > _col)
			{
				int j = _col + 1;
				for (int i = _row + 1; i < nextRow; i++)
				{
					if (pieces[i][j])
						return false;
					j++;
				}
			}
			else
			{
				int j = _col - 1;
				for (int i = _row + 1; i < nextRow; i++)
				{
					if (pieces[i][j])
						return false;
					j--;
				}
			}
		}
		else
		{
			if (nextCol == _col)
			{
				int j = _col;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
				}
			}
			else if (nextCol > _col)
			{
				int j = _col + 1;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
					j++;
				}
			}
			else
			{
				int j = _col - 1;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
					j--;
				}
			}
		}
		if (pieces[nextRow][nextCol])
		{
			if (pieces[nextRow][nextCol]->isWhite() == this->_isWhite)
			{
				return false;
			}
		}
		return true;
	}
};

