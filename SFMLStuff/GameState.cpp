#include "GameState.h"

void GameState::draw(ChessGame& game)
{
	game._window.clear();
	game._window.draw(game._board);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (game._pieces[i][j] && (game._currentChosen != game._pieces[i][j]))
				game._window.draw(*game._pieces[i][j]);

	if (game._currentChosen)
		game._window.draw(*game._currentChosen);

	FullTime fullTime = game._time[game._isWhiteTurn].getRemainingTime();
	std::cout << fullTime._hours << "h " << fullTime._minutes << "m " << fullTime._seconds << "s" << std::endl;

	game._window.display();
}
