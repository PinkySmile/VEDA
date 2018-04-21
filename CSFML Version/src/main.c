#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "functions.h"
#include "macros.h"

sfRenderWindow	**window;

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

void	sighandler(int signum)
{
	if (*window)
		sfRenderWindow_close(*window);
	else
		exit(EXIT_SUCCESS);
	printf("%s: Caught signal %i (%s). Exiting.\n", INFO, signum, strsignal(signum));
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
	for (int i = 0; i < game->fonts.length; i++)
		if (((sfFont **)game->fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game->fonts.content)[i]);
	free(game->fonts.content);
	sfRectangleShape_destroy(game->rectangle);
	sfRenderWindow_destroy(game->window);
	sfText_destroy(game->text);
	sfImage_destroy(game->icon.image);
	sfTexture_destroy(game->icon.texture);
	sfSprite_destroy(game->icon.sprite);
	for (int i = 0; game->buttons[i].content; i++)
		sfRectangleShape_destroy(game->buttons[i].rect);
	free(game->buttons);
	for (int i = 0; game->languages && game->languages[i].name; i++) {
		for (int j = 0; game->languages[i].buttons && game->languages[i].buttons[j]; j++)
			free(game->languages[i].buttons[j]);
		for (int j = 0; game->languages[i].items && game->languages[i].items[j]; j++)
			free(game->languages[i].items[j]);
		for (int j = 0; game->languages[i].keys && game->languages[i].keys[j]; j++)
			free(game->languages[i].keys[j]);
		free(game->languages[i].buttons);
		free(game->languages[i].keys);
		free(game->languages[i].items);
		free(game->languages[i].name);
	}
	for (int i = 0; i < game->characters.length; i++) {
		sfClock_destroy(((Character *)game->characters.content)[i].movement.animationClock);
		sfClock_destroy(((Character *)game->characters.content)[i].movement.stateClock);
	}
	free(game->languages);
}

int	main(int argc, char *args)
{
	game_t	game;

	window = & game.window;
	signal(2, &sighandler);
	printf("%s: Initializating game\n", INFO);
	initGame(&game);
	game.debug = argc >= 2;
	launchGame(&game);
	saveSettings(&game);
	destroyStruct(&game);
	printf("%s: Goodbye !\n", INFO);
	return (EXIT_SUCCESS);
}
