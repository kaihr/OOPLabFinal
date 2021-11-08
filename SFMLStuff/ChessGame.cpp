#include <iostream>
#include "ChessGame.h"

ChessGame::ChessGame() : currentChosen(NULL), window(sf::VideoMode(800, 600), "Chess")
{
	board.loadTileSet("Assets\\tileset.png");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pieces[i][j] = NULL;

	for (int i = 0; i < 8; i++) {
		pieces[0][i] = new Pawn(0, i);
		pieces[1][i] = new Pawn(1, i);
		pieces[6][i] = new Pawn(6, i);
		pieces[7][i] = new Pawn(7, i);
	}
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
