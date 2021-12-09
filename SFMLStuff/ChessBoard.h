#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Piece.h"
#include "Constants.h"
#include "TextureManager.h"

class ChessBoard : public sf::Drawable, public sf::Transformable 
{
private:
	sf::VertexArray _verticesArray;

public:
	ChessBoard();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		states.transform *= getTransform();
		states.texture = &TextureManager::getTexture(TILE_SET);
		target.draw(_verticesArray, states);
	}

public:
	void highlightCell(Piece* chosen, bool hightlight, Piece *pieces[BOARD_SIZE][BOARD_SIZE]);
};