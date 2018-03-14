#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "structs.h"

void	initGame(game_t *game);
char	*concat(char *str1, char *str2, bool free1, bool free2);
void	launchGame(game_t *game);
void	manageEvents(game_t *game);
Array	loadMusics();
Array	loadSprites();
Array	loadSfx();

#endif