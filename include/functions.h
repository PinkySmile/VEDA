#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>

void		launchGame();
void		manageEvents();
void		manage_mouse_click(sfMouseButtonEvent event);
void		changeScreenMode(int new);
void		movePlayer();
char		*executeCommand(char *cmd, char *args);

#endif
