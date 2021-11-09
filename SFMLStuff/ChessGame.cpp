#include <iostream>
#include "ChessGame.h"

ChessGame::ChessGame() : currentChosen(NULL), window(sf::VideoMode(800, 600), "Chess")
{
	board.loadTileSet("Assets\\tileset.png");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pieces[i][j] = NULL;

	for (int i = 0; i < 8; i++) {
		pieces[1][i] = new Pawn(1, i, false);
		pieces[6][i] = new Pawn(6, i);
	}

	pieces[0][0] = new Rook(0, 0, false);
	pieces[0][7] = new Rook(0, 7, false);
	pieces[7][0] = new Rook(7, 0);
	pieces[7][7] = new Rook(7, 7);

	pieces[0][1] = new Knight(0, 1, false);
	pieces[0][6] = new Knight(0, 6, false);
	pieces[7][1] = new Knight(7, 1);
	pieces[7][6] = new Knight(7, 6);

	pieces[0][2] = new Bishop(0, 2, false);
	pieces[0][5] = new Bishop(0, 5, false);
	pieces[7][2] = new Bishop(7, 2);
	pieces[7][5] = new Bishop(7, 5);

	pieces[0][3] = new Queen(0, 3, false);
	pieces[7][3] = new Queen(7, 3);

	pieces[0][4] = new King(0, 4, false);
	pieces[7][4] = new King(7, 4);
}

void ChessGame::handleInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (currentChosen) {
			currentChosen = currentChosen->handleInput(event, pieces);
		}

		else if (!currentChosen) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(window));
				if (pieces[cell.x][cell.y])
					currentChosen = pieces[cell.x][cell.y];
			}
		}
	}
}

void ChessGame::draw()
{
	window.clear();

	window.draw(board);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (pieces[i][j] && (currentChosen != pieces[i][j]))
				window.draw(*pieces[i][j]);

	if (currentChosen) {
		currentChosen->moveWithMouse(window);
		window.draw(*currentChosen);
	}

	window.display();
}

void ChessGame::run()
{
	std::cout << window.isOpen() << std::endl;
	while (window.isOpen())
	{
		handleInput();
        draw();
	}
}
