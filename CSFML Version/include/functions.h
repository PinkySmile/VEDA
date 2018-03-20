#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "structs.h"

void		initGame(game_t *game);
char		*concat(char *str1, char *str2, bool free1, bool free2);
void		launchGame(game_t *game);
void		manageEvents(game_t *game);
void		image(game_t *game, sfSprite *sprite, int x, int y, int width, int height);
void		mainMenu(game_t *game);
Array		loadMusics(game_t *game);
Array		loadSprites(game_t *game);
Array		loadSfx(game_t *game);
Settings	loadSettings();
void		saveSettings(game_t *game);
char		*getButtonContent(int nameId, game_t *game);
Button		*loadButtons(game_t *game);
void		disableButtons(game_t *game);
void		disp_buttons(game_t *game);
void		play_button(game_t *game, int buttonId);
char		*int_to_str(int nb);
void		text(char *str, game_t *game, int x, int y);
void		rect(game_t *game, int x, int y, int width, int height);
Array		loadFonts(game_t *game);
int		get_nbrlen(int nbr);
void		displayLoadingBar(game_t *game, int step, int maxSteps, int file, int maxFiles, char *status);
void		setFont(sfText *text, sfFont *font);
Language	*loadLanguages(game_t *game);
int		getLanguage(Language *languages, char *lang_id);

#endif
