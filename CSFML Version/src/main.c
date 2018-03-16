#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "functions.h"
#include "macros.h"

char	*strsignal(int signum)
{
	switch (signum) {
	case 2:
		return ("Interrupted");
	case 3:
		return ("Quit");
	case 4:
		return ("Illegal hardware instruction");
	case 6:
		return ("Aborted");
	case 7:
		return ("Bus error");
	case 8:
		return ("Floating point exception");
	case 10:
		return ("User defined signal 1");
	case 11:
		return ("Segmentation fault");
	case 12:
		return ("User defined signal 2");
	case 13:
		return ("Broken pipe");
	case 14:
		return ("Timer expired");
	case 15:
		return ("Terminated");
	default:
		return ("Unknown signal");
	}
}

void	destroyStruct(game_t *game)
{
	printf("%s: Destroying game objects\n", INFO);
	for (int i = 0; i < game->sprites.length; i++) {
		if (((Sprite *)game->sprites.content)[i].sprite != NULL)
			sfSprite_destroy(((Sprite *)game->sprites.content)[i].sprite);
		if (((Sprite *)game->sprites.content)[i].texture != NULL)
			sfTexture_destroy(((Sprite *)game->sprites.content)[i].texture);
	}
	free(game->sprites.content);
	for (int i = 0; i < game->musics.length; i++)
		if (((sfMusic **)game->musics.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game->musics.content)[i]);
	free(game->musics.content);
	for (int i = 0; i < game->sfx.length; i++)
		if (((sfMusic **)game->sfx.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game->sfx.content)[i]);
	free(game->sfx.content);
}

int	main()
{
	game_t	game;

	printf("%s: Initializating game\n", INFO);
	initGame(&game);
	launchGame(&game);
	destroyStruct(&game);
	printf("%s: Goodbye !\n", INFO);
	return (EXIT_SUCCESS);
}
