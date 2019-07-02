#ifndef __BATTLE_STRUCT_HEADER_
#define __BATTLE_STRUCT_HEADER_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <lua.h>
#include "data_structures/array.h"
#include "character.h"
#include "list.h"
#include "sprite.h"
#include "enums.h"

typedef struct {
	Sprite		bossSprite;
	bool		needToDestroySprite;
	sfMusic		*music;
	bool		needToDestroyMusic;
	enum battles	type;
	Character	boss;
	sfVector2f	bossHitbox;
	sfVector2f	playerHitbox;
	list_t		projectiles;
	Array		projectileBank;
	char		*name;
	char		*script;
	sfClock		*clock;
	bool		timeStopped;
	int		yieldTime;
	lua_State	*lua;
	lua_State	*lua_thread;
} Battle;

#endif