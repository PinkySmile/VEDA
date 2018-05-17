#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "macros.h"
#ifdef __MINGW32__
#	include <windows.h>
#endif

#ifndef SIGBUS
#	define SIGBUS 7
#endif
#ifndef SIGQUIT
#	define SIGQUIT 3
#endif

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
	if (signum == SIGINT || signum == SIGTERM) {
		if (*window)
			sfRenderWindow_close(*window);
		else
			exit(EXIT_SUCCESS);
		printf("%s: Caught signal %i (%s). Exiting.\n", INFO, signum, strsignal(signum));
	} else {
		printf("%s: Caught signal %i (%s). Aborting !\n", FATAL, signum, strsignal(signum));
		#ifdef __MINGW32__
			MessageBox(NULL, concatf("Error: Caught signal %i (%s)\n\n\nClick OK to close the program", signum, strsignal(signum)), "Fatal Error", 0);
		#endif
		exit(EXIT_FAILURE);
		exit(128 + signum); //In case the first one fail
		raise(SIGKILL); //In case the crash trashed the exit function
		signal(11, NULL);
		*(char *)NULL = *(char *)NULL; //Let's do this kernel. Come on, I wait you !
	}
}

void	destroyStruct(game_t *game)
{
	printf("%s: Destroying game objects\n", INFO);
	for (int i = 0; i < game->sprites.length; i++) {
		printf("%s: Destroying sprite %i\n", INFO, i);
		if (((Sprite *)game->sprites.content)[i].sprite != NULL)
			sfSprite_destroy(((Sprite *)game->sprites.content)[i].sprite);
		if (((Sprite *)game->sprites.content)[i].texture != NULL)
			sfTexture_destroy(((Sprite *)game->sprites.content)[i].texture);
	}
	free(game->sprites.content);
	for (int i = 0; i < game->musics.length; i++) {
		printf("%s: Destroying music %i\n", INFO, i);
		if (((sfMusic **)game->musics.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game->musics.content)[i]);
	}
	free(game->musics.content);
	for (int i = 0; i < game->sfx.length; i++) {
		printf("%s: Destroying sfx %i\n", INFO, i);
		if (((sfMusic **)game->sfx.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game->sfx.content)[i]);
	}
	free(game->sfx.content);
	for (int i = 0; i < game->fonts.length; i++) {
		printf("%s: Destroying font %i\n", INFO, i);
		if (((sfFont **)game->fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game->fonts.content)[i]);
	}
	free(game->fonts.content);
	sfRectangleShape_destroy(game->rectangle);
	sfRenderWindow_destroy(game->window);
	sfText_destroy(game->text);
	sfImage_destroy(game->icon.image);
	sfTexture_destroy(game->icon.texture);
	sfSprite_destroy(game->icon.sprite);
	for (int i = 0; game->buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO, i);
		sfRectangleShape_destroy(game->buttons[i].rect);
	}
	for (int i = 0; game->languages && game->languages[i].name; i++) {
		printf("%s: Destroying language %i (%s)\n", INFO, i, game->languages[i].name);
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
		printf("%s: Destroying character %i (%s)\n", INFO, i, ((Character *)game->characters.content)[i].name);
		sfClock_destroy(((Character *)game->characters.content)[i].movement.animationClock);
		sfClock_destroy(((Character *)game->characters.content)[i].movement.stateClock);
		sfClock_destroy(((Character *)game->characters.content)[i].stats.energyRegenClock);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			sfClock_destroy(((Character *)game->characters.content)[i].damageClock[j]);
	}
	for (int i = 0; i < NB_OF_KEYS; i++)
		if (game->settings.keys[i] > 204 && game->settings.keys[i] != (unsigned char)-1)
			free(game->buttons[i + game->languagesConf.y + game->languagesConf.x].content);
	free(game->buttons);
	free(game->characters.content);
	free(game->languages);
}

int	main(int argc, char **args)
{
	game_t	game;

	srand((long)&game);
	window = &game.window;
	signal(SIGINT,  &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGILL,  &sighandler);
	signal(SIGABRT, &sighandler);
	signal(SIGBUS,  &sighandler);
	signal(SIGFPE,  &sighandler);
	signal(SIGSEGV, &sighandler);
	signal(SIGTERM, &sighandler);
	printf("%s: Initializating game\n", INFO);
	initGame(&game);
	game.debug = (argc == 2 && !strcmp("debug", args[1]));
	launchGame(&game);
	saveSettings(&game);
	destroyStruct(&game);
	printf("%s: Goodbye !\n", INFO);
	return (EXIT_SUCCESS);
}
