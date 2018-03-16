#include "structs.h"
#include "functions.h"

void	play_button(game_t *game, int buttonID)
{
	game->menu = buttonID / buttonID;
	disableButtons(game);
}