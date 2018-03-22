#include "structs.h"

void	

void	inGame(game_t *game)
{
	displayLowerLayer(game->map, game->sprites);
	displayCharacters(game->player, game->characters, game->sprites);
	displayUpperLayer(game->map, game->sprites);
}