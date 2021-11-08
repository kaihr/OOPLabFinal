#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Utility 
{
public:
	static sf::Vector2i getCell(sf::Vector2i coords) {
		return sf::Vector2i(coords.y / CELL_LENGTH, coords.x / CELL_LENGTH);
	}
};