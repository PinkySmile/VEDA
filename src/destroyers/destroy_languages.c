#include <malloc.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyLanguages()
{
	for (int i = 0; game.resources.languages && game.resources.languages[i].name; i++) {
		if (game.debug)
			printf("%s: Destroying language %i (%s)\n", INFO_BEG, i, game.resources.languages[i].name);
		for (int j = 0; game.resources.languages[i].buttons && game.resources.languages[i].buttons[j]; j++)
			free(game.resources.languages[i].buttons[j]);
		for (int j = 0; game.resources.languages[i].items && game.resources.languages[i].items[j]; j++)
			free(game.resources.languages[i].items[j]);
		for (int j = 0; game.resources.languages[i].keys && game.resources.languages[i].keys[j]; j++)
			free(game.resources.languages[i].keys[j]);
		free(game.resources.languages[i].buttons);
		free(game.resources.languages[i].keys);
		free(game.resources.languages[i].items);
		free(game.resources.languages[i].name);
	}
	free(game.resources.languages);
	for (int i = 0; i < NB_OF_KEYS; i++)
		if (game.settings.keys[i] > 204 && game.settings.keys[i] != (unsigned char)-1)
			free(game.resources.buttons[i + game.languagesConf.y + game.languagesConf.x].content);
}
