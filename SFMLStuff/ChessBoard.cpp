#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	_verticesArray.setPrimitiveType(sf::PrimitiveType::Quads);
	_verticesArray.resize(8 * 8 * 4);

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int id = (row * 8 + col) * 4;
			sf::Vertex* currentQuad = &_verticesArray[id];

			currentQuad[0].position = sf::Vector2f(col * CELL_LENGTH, row * CELL_LENGTH);
			currentQuad[1].position = sf::Vector2f((col + 1) * CELL_LENGTH, row * CELL_LENGTH);
			currentQuad[2].position = sf::Vector2f((col + 1) * CELL_LENGTH, (row + 1) * CELL_LENGTH);
			currentQuad[3].position = sf::Vector2f(col * CELL_LENGTH, (row + 1) * CELL_LENGTH);

			int parity = (row + col) % 2;

			currentQuad[0].texCoords = sf::Vector2f(parity * CELL_LENGTH, 0);
			currentQuad[1].texCoords = sf::Vector2f((parity + 1) * CELL_LENGTH, 0);
			currentQuad[2].texCoords = sf::Vector2f((parity + 1) * CELL_LENGTH, CELL_LENGTH);
			currentQuad[3].texCoords = sf::Vector2f(parity * CELL_LENGTH, CELL_LENGTH);
		}
	}
}

void ChessBoard::highlightCell(Piece* chosen, bool hightlight, Piece *pieces[BOARD_SIZE][BOARD_SIZE])
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int id = (row * 8 + col) * 4;
			sf::Vertex* currentQuad = &_verticesArray[id];

			currentQuad[0].position = sf::Vector2f(col * CELL_LENGTH, row * CELL_LENGTH);
			currentQuad[1].position = sf::Vector2f((col + 1) * CELL_LENGTH, row * CELL_LENGTH);
			currentQuad[2].position = sf::Vector2f((col + 1) * CELL_LENGTH, (row + 1) * CELL_LENGTH);
			currentQuad[3].position = sf::Vector2f(col * CELL_LENGTH, (row + 1) * CELL_LENGTH);

			int parity = (row + col) % 2;

			if (hightlight && chosen->validAndNotInCheck(row, col, pieces)) {
				if ((!pieces[row][col] || pieces[row][col]->isWhite() != chosen->isWhite()))
					parity += 2;
			}

			currentQuad[0].texCoords = sf::Vector2f(parity * CELL_LENGTH, 0);
			currentQuad[1].texCoords = sf::Vector2f((parity + 1) * CELL_LENGTH, 0);
			currentQuad[2].texCoords = sf::Vector2f((parity + 1) * CELL_LENGTH, CELL_LENGTH);
			currentQuad[3].texCoords = sf::Vector2f(parity * CELL_LENGTH, CELL_LENGTH);
		}
	}
}
