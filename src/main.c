#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <discord_rpc.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "macros.h"
#include "discord_rp.h"

#ifndef SIGBUS
#	define SIGBUS 7
#endif
#ifndef SIGQUIT
#	define SIGQUIT 3
#endif

game_t  game;
int	nbSignals = 0;

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

void	destroyBattle(Battle battle)
{
	list_t	*list = &battle.projectiles;

	if (battle.Lua) {
		sfClock_destroy(battle.clock);
		free(battle.script);
		free(battle.name);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			sfClock_destroy(battle.boss.damageClock[j]);
		if (battle.bossSprite.sprite && battle.needToDestroySprite) {
			sfSprite_destroy(battle.bossSprite.sprite);
			sfTexture_destroy(battle.bossSprite.texture);
		}
	        for (int i = 0; i < battle.projectileBank.length; i++) {
			Projectile	*proj = &((Projectile *)battle.projectileBank.content)[i];

			if (proj->needToDestroySprite) {
				sfSprite_destroy(proj->sprite.sprite);
				sfTexture_destroy(proj->sprite.texture);
			}
		}
		free(battle.projectileBank.content);
		battle.projectileBank.length = 0;
		for (; list->next; list = list->next);
		for (; list && list->data; list = list->prev) {
			Projectile	*proj = list->data;

			sfClock_destroy(proj->clock);
			sfClock_destroy(proj->animClock);
			free(list->data);
			free(list->next);
		}
		if (battle.music && battle.needToDestroyMusic) {
			sfMusic_stop(battle.music);
			sfMusic_destroy(battle.music);
		}
		if (battle.Lua)
			lua_close(battle.Lua);
	}
}

void	destroyStruct()
{
	printf("%s: Destroying game objects\n", INFO);
	for (int i = 0; i < game.ressources.sprites.length; i++) {
		printf("%s: Destroying sprite %i\n", INFO, i);
		if (((Sprite *)game.ressources.sprites.content)[i].sprite != NULL)
			sfSprite_destroy(((Sprite *)game.ressources.sprites.content)[i].sprite);
		if (((Sprite *)game.ressources.sprites.content)[i].texture != NULL)
			sfTexture_destroy(((Sprite *)game.ressources.sprites.content)[i].texture);
	}
	free(game.ressources.sprites.content);
	for (int i = 0; i < game.ressources.musics.length; i++) {
		printf("%s: Destroying music %i\n", INFO, i);
		if (((sfMusic **)game.ressources.musics.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game.ressources.musics.content)[i]);
	}
	free(game.ressources.musics.content);
	for (int i = 0; i < game.ressources.sfx.length; i++) {
		printf("%s: Destroying sfx %i\n", INFO, i);
		if (((sfMusic **)game.ressources.sfx.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game.ressources.sfx.content)[i]);
	}
	free(game.ressources.sfx.content);
	for (int i = 0; i < game.ressources.fonts.length; i++) {
		printf("%s: Destroying font %i\n", INFO, i);
		if (((sfFont **)game.ressources.fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game.ressources.fonts.content)[i]);
	}
	free(game.ressources.fonts.content);
	sfRectangleShape_destroy(game.ressources.rectangle);
	sfRenderWindow_destroy(game.ressources.window);
	sfText_destroy(game.ressources.text);
	sfImage_destroy(game.ressources.icon.image);
	sfTexture_destroy(game.ressources.icon.texture);
	sfSprite_destroy(game.ressources.icon.sprite);
	if (game.ressources.dialogLuaScript)
		lua_close(game.ressources.dialogLuaScript);
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO, i);
		sfRectangleShape_destroy(game.ressources.buttons[i].rect);
	}
	for (int i = 0; game.ressources.languages && game.ressources.languages[i].name; i++) {
		printf("%s: Destroying language %i (%s)\n", INFO, i, game.ressources.languages[i].name);
		for (int j = 0; game.ressources.languages[i].buttons && game.ressources.languages[i].buttons[j]; j++)
			free(game.ressources.languages[i].buttons[j]);
		for (int j = 0; game.ressources.languages[i].items && game.ressources.languages[i].items[j]; j++)
			free(game.ressources.languages[i].items[j]);
		for (int j = 0; game.ressources.languages[i].keys && game.ressources.languages[i].keys[j]; j++)
			free(game.ressources.languages[i].keys[j]);
		free(game.ressources.languages[i].buttons);
		free(game.ressources.languages[i].keys);
		free(game.ressources.languages[i].items);
		free(game.ressources.languages[i].name);
	}
	for (int i = 0; i < game.state.characters.length; i++) {
		printf("%s: Destroying character %i (%s)\n", INFO, i, ((Character *)game.state.characters.content)[i].name);
		sfClock_destroy(((Character *)game.state.characters.content)[i].movement.animationClock);
		sfClock_destroy(((Character *)game.state.characters.content)[i].movement.stateClock);
		sfClock_destroy(((Character *)game.state.characters.content)[i].stats.energyRegenClock);
		free(((Character *)game.state.characters.content)[i].battleScript);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			sfClock_destroy(((Character *)game.state.characters.content)[i].damageClock[j]);
	}
	for (int i = 0; i < NB_OF_KEYS; i++)
		if (game.settings.keys[i] > 204 && game.settings.keys[i] != (unsigned char)-1)
			free(game.ressources.buttons[i + game.languagesConf.y + game.languagesConf.x].content);
	free(game.ressources.buttons);
	free(game.state.characters.content);
	free(game.ressources.languages);
	printf("%s: Destroying battle sounds\n", INFO);
	playSound(NULL, true);
	printf("%s: Destroying battle struct\n", INFO);
	destroyBattle(game.state.battle_infos);
}

void	sighandler(int signum)
{
	nbSignals++;
	if (nbSignals >= 6) {
		signal(signum, NULL);
		raise(signum);
		exit(EXIT_FAILURE);
	}
	if (nbSignals >= 3)
		return;
	if (signum == SIGINT || signum == SIGTERM) {
		if (game.ressources.window && sfRenderWindow_isOpen(game.ressources.window))
			sfRenderWindow_close(game.ressources.window);
		else {
			Discord_Shutdown();
			exit(EXIT_SUCCESS);
		}
		printf("%s: Caught signal %i (%s). Exiting.\n", INFO, signum, strsignal(signum));
	} else {
		updateDiscordPresence("Game crashed", strsignal(signum), 0, false, "icon", "bug", "VEDA", strsignal(signum));
		printf("%s: Caught signal %i (%s). Aborting !\n", FATAL, signum, strsignal(signum));
		dispMsg("Fatal Error", concatf("Fatal: Caught signal %i (%s)\n\n\nClick OK to close the program", signum, strsignal(signum)), 0);
		Discord_Shutdown();
		exit(EXIT_FAILURE);
		signal(signum, NULL);
		raise(signum); //In case the crash trashed the exit function
		signal(11, NULL);
		*(char *)NULL = *(char *)NULL; //Let's do this kernel. Come on, I wait you !
	}
}

int	main(int argc, char **args)
{
	game.ressources.window = NULL;
	srand((long)&game);
	signal(SIGINT,  &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGILL,  &sighandler);
	signal(SIGABRT, &sighandler);
	signal(SIGBUS,  &sighandler);
	signal(SIGFPE,  &sighandler);
	signal(SIGSEGV, &sighandler);
	signal(SIGTERM, &sighandler);
	printf("%s: Init discord rich presence\n", INFO);
	initDiscordRichPresence();
	printf("%s: Initializating game\n", INFO);
	initGame();
	game.debug = (argc == 2 && !strcmp("debug", args[1]));
	updateDiscordPresence("Main menu", "In Main Menu", 0, false, "icon", "nem", "VEDA", "Main Menu");
	launchGame();
	saveSettings();
	destroyStruct();
	printf("%s: Goodbye !\n", INFO);
	Discord_Shutdown();
	return (EXIT_SUCCESS);
}
