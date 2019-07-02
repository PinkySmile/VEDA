#ifndef __GAME_STRUCT_HEADER_
#define __GAME_STRUCT_HEADER_

#include <SFML/Graphics.h>
#include <lua.h>
#include "icon.h"
#include "data_structures/button.h"
#include "data_structures/array.h"
#include "language.h"
#include "settings.h"
#include "sprite.h"
#include "object.h"
#include "data_structures/battle.h"

typedef struct {
	char		*displayedText;
	sfUint8		*dialogOwnerName;
	char		*rawText;
	int		index;
	float		speed;
	sfSound		*sound;
	Sprite		*sprite;
	sfClock		*clock;
} DialogDisplayed;

typedef struct {
	sfUint32	buffer[BUFFER_MAX_SIZE + 1];
	int		bufPos;
	int		bufSize;
} Input;

typedef struct {
	Object		*objects;
	Sprite		background;
	char		*backgroundPath;
	char		*path;
} Map;

typedef struct {
	int		menu;
	sfVector2i	cameraPos;
	Array		characters;
	Battle		battle_infos;
	Map		loadedMap;
	int		dialogs;
	DialogDisplayed	*dialogsOnScreen;
	int		menuSelected;
	sfVideoMode	currentDesktopMode;
} GameState;

typedef struct {
	Icon		icon;
	Button		*buttons;
	Array		sprites;
	Array		musics;
	Array		sfx;
	Array		fonts;
	sfRenderWindow	*window;
	sfView		*view;
	Language	*languages;
	sfRectangleShape*rectangle;
	sfCircleShape	*circle;
	sfText		*text;
	lua_State	*dialogLuaScript;
} Resources;

typedef struct game_s {
	char		version[10];
	bool		debug;
	Settings	settings;
	GameState	state;
	Resources	resources;
	Input		input;
	sfVector2i	languagesConf;
	sfVector2u	newSize;
	enum windowMode	newMode;
} game_t;

#endif