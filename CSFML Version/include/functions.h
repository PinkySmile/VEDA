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
Array		loadMusics(game_t *game);
Array		loadSprites(game_t *game);
Array		loadSfx(game_t *game);
Settings	loadSettings();
void		saveSettings(game_t *game);
char		*getButtonContent(int nameId, game_t *game);
Button		*loadButtons(game_t *game);
void		disp_buttons(game_t *game);
char		*int_to_str(int nb);
void		text(char *str, game_t *game, int x, int y);
void		rect(game_t *game, int x, int y, int width, int height);
Array		loadFonts(game_t *game);
int		get_nbrlen(int nbr);
void		displayLoadingBar(game_t *game, int step, int maxSteps, int file, int maxFiles, char *status);
void		setFont(sfText *text, sfFont *font);
Language	*loadLanguages(game_t *game);
int		getLanguage(Language *languages, char *lang_id);
void		manage_mouse_click(game_t *game, sfMouseButtonEvent event);
Object		*loadLevel(char *path, char **bg_path);
char		*getKeyString(unsigned char keyID);
void		setVolumes(Array sounds, float volume);
float		isPressed(int keyID);
char		*getVersion();
void		changeScreenMode(game_t *game, int new);

//Menu functions
void		mainMenu(game_t *game);
void		inGame(game_t *game);
void		controls(game_t *game);
void		audio(game_t *game);
void		options(game_t *game);

//callbacks
void		play_button(game_t *game, int buttonId);
void		quit_button(game_t *game, int buttonId);
void		settings_button(game_t *game, int buttonId);
void		options_button(game_t *game, int buttonID);
void		audio_button(game_t *game, int buttonID);
void		lang_button(game_t *game, int buttonID);
void		controls_button(game_t *game, int buttonID);
void		back_on_title_screen(game_t *game, int buttonID);
void		changeLanguage(game_t *game, int buttonID);
void		changeKey(game_t *game, int buttonID);
void		fullScreen(game_t *game, int buttonID);
void		borderless(game_t *game, int buttonID);
void		windowed(game_t *game, int buttonID);

#endif
