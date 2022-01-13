#pragma once

#include <string>

const float MENU_OPTION_WIDTH = 250;
const float MENU_OPTION_HEIGHT = 80;

const sf::Color BG_COLOR(50, 50, 50);
const sf::Color RECT_COLOR(206, 216, 229);
const sf::Color ACTIVE_RECT_COLOR(236, 246, 255);
const sf::Vector2f RECT_SIZE(MENU_OPTION_WIDTH, MENU_OPTION_HEIGHT);

const int N_CONFIG_BUTTON = 9;
const sf::Color CONFIG_BUTTON_COLOR(255, 178, 102);
const sf::Color CONFIG_BUTTON_ACTIVE_COLOR(255, 204, 102);
const std::string CONFIG_BUTTON_LABEL[N_CONFIG_BUTTON] = {
	"02h00",
	"01h00",
	"30m00",
	"15m00",
	"10m00",
	"05m00",
	"03m00",
	"02m00",
	"01m00"
};


const int CELL_LENGTH = 75;
const int BOARD_SIZE = 8;

const int PAWN_SCORE = 1;
const int KNIGHT_SCORE = 3;
const int BISHOP_SCORE = 3;
const int ROOK_SCORE = 5;
const int QUEEN_SCORE = 9;

enum class PIECES {
	WHITE_PAWN,
	WHITE_ROOK,
	WHITE_BISHOP,
	WHITE_KING,
	WHITE_QUEEN,
	WHITE_KNIGHT,

	BLACK_PAWN,
	BLACK_ROOK,
	BLACK_BISHOP,
	BLACK_KING,
	BLACK_QUEEN,
	BLACK_KNIGHT,

	TILE_SET,
	BACKGROUND,

	N_TEXTURES
};
