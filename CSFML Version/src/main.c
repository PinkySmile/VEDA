#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "structs.h"
#include "functions.h"

void	destroyStruct(game_t *game)
{
	
}

int	main()
{
	game_t	game;
	
	initGame(&game);
	launchGame(&game);
	destroyStruct(&game);
	return (0);
}