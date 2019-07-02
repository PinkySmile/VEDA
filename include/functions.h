#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "data_structures/game_struct.h"

void	sighandler(int signum);
void	launchGame();
void	manageEvents();
void	manageMouseClick(sfMouseButtonEvent event);
void	changeScreenMode(int new);
char	*executeCommand(char *cmd, char **args);
void	resolveCommand(DialogDisplayed *diag);
bool	addCharacter(char c, char **str, bool reallocBuffer);

#endif
