#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Piece.h"
#include "Constants.h"

class ChessBoard : public sf::Drawable, public sf::Transformable 
{
private:
	sf::Texture _tileSet;
	sf::VertexArray _verticesArray;

public:
	ChessBoard();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		states.transform *= getTransform();
		states.texture = &_tileSet;
		target.draw(_verticesArray, states);
	}
};