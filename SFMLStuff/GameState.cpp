#include "GameState.h"
#include "Button.h"

const sf::Color BG_COLOR(50, 50, 50);

void GameState::draw(ChessGame& game)
{
	game._window.clear(BG_COLOR);
	game._window.draw(game._board);


	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (game._pieces[i][j] && (game._currentChosen != game._pieces[i][j]))
				game._window.draw(*game._pieces[i][j]);

	if (game._currentChosen)
		game._window.draw(*game._currentChosen);

	FullTime fullTime = game._time[game._isWhiteTurn].getRemainingTime();
	// std::cout << fullTime._hours << "h " << fullTime._minutes << "m " << fullTime._seconds << "s" << std::endl;

	game._window.draw(game._time[0]);
	game._window.draw(game._time[1]);

	game._window.display();
}
