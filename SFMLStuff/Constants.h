#pragma once

const sf::Color BG_COLOR(50, 50, 50);

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

	N_TEXTURES
};
