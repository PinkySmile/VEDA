#include <malloc.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyLanguages()
{
	for (int i = 0; game.ressources.languages && game.ressources.languages[i].name; i++) {
		if (game.debug)
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
	free(game.ressources.languages);
	for (int i = 0; i < NB_OF_KEYS; i++)
		if (game.settings.keys[i] > 204 && game.settings.keys[i] != (unsigned char)-1)
			free(game.ressources.buttons[i + game.languagesConf.y + game.languagesConf.x].content);
}
