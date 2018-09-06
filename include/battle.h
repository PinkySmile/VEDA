#ifndef __BATTLE_STRUCT_HEADER_
#define __BATTLE_STRUCT_HEADER_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <lua.h>
#include "array.h"
#include "character.h"
#include "list.h"
#include "sprite.h"
#include "enums.h"

typedef struct {
	enum battles	type;
	Character	boss;
	sfVector2f	bossHitbox;
	Sprite		bossSprite;
	Character	*player;
	sfVector2f	playerHitbox;
	list_t		projectiles;
	Array		projectileBank;
	bool		needToDestroySprite;
	bool		needToDestroyMusic;
	sfMusic		*music;
	char		*name;
	char		*script;
	sfClock		*clock;
	bool		timeStopped;
	int		yieldTime;
	lua_State	*Lua;
	lua_State	*Lua_thread;
} Battle;

#endif