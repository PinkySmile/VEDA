#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "structs.h"

char		*concat(char *str1, char *str2, bool free1, bool free2);
void		launchGame(game_t *game);
void		manageEvents(game_t *game);
char		*getButtonContent(int nameId, game_t *game);
char		*int_to_str(int nb);
int		get_nbrlen(int nbr);
void		setFont(sfText *text, sfFont *font);
int		getLanguage(Language *languages, char *lang_id);
void		manage_mouse_click(game_t *game, sfMouseButtonEvent event);
char		*getKeyString(unsigned char keyID);
void		setVolumes(Array sounds, float volume);
float		isPressed(int keyID, sfRenderWindow *window);
char		*getVersion();
void		changeScreenMode(game_t *game, int new);
int		dispMsg(char *title, char *content, int variate);
Character	*getPlayer(Character *characters, int len);
char		**split(char *str, char separator);
void		displayCharacter(Character *character, game_t *game, int id, sfSprite *sprite);
void		displayCharacters(game_t *game);
void		displayLowerLayer(game_t *game);
void		displayUpperLayer(game_t *game);
void		displayHUD(game_t *game);
void		movePlayer(game_t *game);
int		playSound(char const *path, bool freeAll);

//Init game struct
void		initGame	(game_t *game);
Array		loadMusics	(game_t *game);
Array		loadSprites	(game_t *game);
Array		loadSfx		(game_t *game);
Array		loadFonts	(game_t *game);
Button		*loadButtons	(game_t *game);
Language	*loadLanguages	(game_t *game);
Sprite		createSprite	(Sprite_config config);
sfMusic		*createMusic	(Music_config config);
void		displayLoadingBar(game_t *game, int step, int maxSteps, int file, int maxFiles, char *status);
Battle		loadBattleScript(char *path);

//Display functions
void	image		(game_t *game, sfSprite *sprite, int x, int y, int width, int height);
void	disp_buttons	(game_t *game);
void	text		(char *str, game_t *game, int x, int y, bool isUnicode);
void	rect		(game_t *game, int x, int y, int width, int height);

//Save/Load functions
bool		saveGame	(game_t *game, bool level);
void		loadGame	(game_t *game);
void		saveSettings	(game_t *game);
Settings	loadSettings	(void);
void		loadLevel	(char *path, game_t *game);
Array		loadCharacters	(char *path);
Object		*loadMap	(char *path, char **bg);

//Menu functions
void	mainMenu	(game_t *game);
void	inGame		(game_t *game);
void	controls	(game_t *game);
void	audio		(game_t *game);
void	options		(game_t *game);
void	buf_modif	(game_t *game);
void	changeName	(game_t *game);
void	chooseCharacter	(game_t *game);
void	battle		(game_t *game);

//callbacks
void	play_button		(game_t *game, int buttonId);
void	quit_button		(game_t *game, int buttonId);
void	settings_button		(game_t *game, int buttonId);
void	options_button		(game_t *game, int buttonID);
void	audio_button		(game_t *game, int buttonID);
void	lang_button		(game_t *game, int buttonID);
void	controls_button		(game_t *game, int buttonID);
void	back_on_title_screen	(game_t *game, int buttonID);
void	changeLanguage		(game_t *game, int buttonID);
void	changeKey		(game_t *game, int buttonID);
void	fullScreen		(game_t *game, int buttonID);
void	borderless		(game_t *game, int buttonID);
void	windowed		(game_t *game, int buttonID);
void	FPS_button		(game_t *game, int buttonID);
void	changePlayerName	(game_t *game, int buttonID);

#endif
