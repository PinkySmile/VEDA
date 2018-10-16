#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "game_struct.h"

void	sighandler(int signum);
void	launchGame();
void	manageEvents();
void	manage_mouse_click(sfMouseButtonEvent event);
void	changeScreenMode(int new);
void	movePlayer();
char	*executeCommand(char *cmd, char **args);
void	resolveCommand(DialogDisplayed *diag);
bool	addCharacter(char c, char **str, bool reallocBuffer);
void	moveCharacter(Character *character, sfVector2f direction);

#endif
