#include "GameState.h"
#include "Button.h"

void GameState::draw(ChessGame& game)
{
	game._window.draw(game._board);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (game._pieces[i][j] && (game._currentChosen != game._pieces[i][j]))
				game._window.draw(*game._pieces[i][j]);

	if (game._currentChosen)
		game._window.draw(*game._currentChosen);

	game._window.draw(game._time[0]);
	game._window.draw(game._time[1]);
}
