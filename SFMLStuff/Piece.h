#pragma once
#include <SFML/Graphics.hpp>

#include "Utility.h"

#include <iostream>

class Piece : public sf::Drawable, public sf::Transformable
{
public:
	enum class Type {
		PAWN,
		ROOK,
		BISHOP,
		KNIGHT,
		QUEEN,
		KING
	};

protected:
	int _row, _col;
	bool _isWhite;
	bool _enPassant;
	bool _hasMoved; //For castling and pawn movement
	Type _type;

	sf::Sprite _sprite;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_sprite, states);
	}

public:
	Piece(int row = 0, int col = 0, bool isWhite = true, Type type = Type::PAWN, bool sEnPassant = false, int sHasMoved = 0) :
		_row(row), _col(col), _isWhite(isWhite), _hasMoved(sHasMoved), _type(type), _enPassant(sEnPassant) {}

	bool isWhite() { return _isWhite; };

	virtual bool validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) { return true; }

	void moveWithMouse(const sf::Window &window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mousePos.x -= CELL_LENGTH / 2;
		mousePos.y -= CELL_LENGTH / 2;

		_sprite.setPosition(sf::Vector2f(mousePos));
	}

public:
	void setPos(int row = -1, int col = -1) {
		if (Utility::inBoard(row, col)) {
			_row = row;
			_col = col;
		}

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	};

public:
	int row() { return _row; }
	int col() { return _col; }

	bool enPassant() { return _enPassant; };
	bool hasMoved() { return _hasMoved; };

	void markAsMoved() { _hasMoved |= 1; };
	void switchEnPassant() { _enPassant ^= 1; };

	Type type() { return _type; };

public:
	bool putKingInDanger(int fromRow, int fromCol, int toRow, int toCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]);
	virtual bool validAndNotInCheck(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]);

public:
	std::string toString() const;
};
