#ifndef __GAME_FUNCTIONS_H_
#define __GAME_FUNCTIONS_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "structs.h"

char		*concat(char *str1, char *str2, bool free1, bool free2);
void		launchGame();
void		manageEvents();
char		*getButtonContent(int nameId);
char		*int_to_str(int nb);
int		get_nbrlen(int nbr);
void		setFont(sfText *text, sfFont *font);
int		getLanguage(Language *languages, char *lang_id);
void		manage_mouse_click(sfMouseButtonEvent event);
char		*getKeyString(unsigned char keyID);
void		setVolumes(Array sounds, float volume);
float		isPressed(int keyID, sfRenderWindow *window);
char		*getVersion();
void		changeScreenMode(int new);
int		dispMsg(char *title, char *content, int variate);
Character	*getPlayer(Character *characters, int len);
char		**split(char *str, char separator);
void		displayCharacter(Character *character, int id, sfSprite *sprite);
void		displayCharacters();
void		displayLowerLayer();
void		displayUpperLayer();
void		displayHUD();
void		movePlayer();
int		playSound(char const *path, bool freeAll);
void		addDependencies(lua_State *Lua);
char		*executeCommand(char *cmd, char *args);

//Init game struct
void		initGame	();
Array		loadMusics	();
Array		loadSprites	();
Array		loadSfx		();
Array		loadFonts	();
Button		*loadButtons	();
Language	*loadLanguages	();
Sprite		createSprite	(Sprite_config config);
sfMusic		*createMusic	(Music_config config);
void		displayLoadingBar(int step, int maxSteps, int file, int maxFiles, char *status);
Battle		loadBattleScript(char *path);

//Display functions
void	image		(sfSprite *sprite, int x, int y, int width, int height);
void	disp_buttons	();
void	text		(char *str, int x, int y, bool isUnicode);
void	rect		(int x, int y, int width, int height);

//Save/Load functions
bool		saveGame	(bool level);
void		loadGame	();
void		saveSettings	();
Settings	loadSettings	(void);
void		loadLevel	(char *path);
Array		loadCharacters	(char *path);
Object		*loadMap	(char *path, char **bg);

//Menu functions
void	mainMenu	();
void	inGame		();
void	controls	();
void	audio		();
void	options		();
void	buf_modif	();
void	changeName	();
void	chooseCharacter	();
void	battle		();

//callbacks
void	play_button		(int buttonId);
void	quit_button		(int buttonId);
void	settings_button		(int buttonId);
void	options_button		(int buttonID);
void	audio_button		(int buttonID);
void	lang_button		(int buttonID);
void	controls_button		(int buttonID);
void	back_on_title_screen	(int buttonID);
void	changeLanguage		(int buttonID);
void	changeKey		(int buttonID);
void	fullScreen		(int buttonID);
void	borderless		(int buttonID);
void	windowed		(int buttonID);
void	FPS_button		(int buttonID);
void	changePlayerName	(int buttonID);

#endif
