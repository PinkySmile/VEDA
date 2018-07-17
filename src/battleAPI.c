#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include "structs.h"
#include "functions.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "concatf.h"

extern	game_t	game;
extern	void	(* const game_functions[])(game_t *game);
extern	const	luaL_Reg	projectiles_lib[];
extern	const	luaL_Reg	character_lib[];

Projectile	*addProjectile(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker)
{
	Projectile	*bank = game.battle_infos.projectileBank.content;
	Projectile	*proj;
	list_t		*list = &game.battle_infos.projectiles;

	for (; list->next && list->data; list = list->next);
	if (list->data) {
		list->next = malloc(sizeof(*list->next));
		if (!list->next)
			return (NULL);
		memset(list->next, 0, sizeof(*list->next));
		list->next->prev = list;
		list = list->next;
	}
	proj = malloc(sizeof(*proj));
	if (!proj && list->prev) {
		list->prev->next = NULL;
		free(list);
		return (NULL);
	}
	list->data = proj;
	*proj = bank[id];
	proj->pos.x = x;
	proj->pos.y = y;
	proj->clock = sfClock_create();
	proj->animClock = sfClock_create();
	proj->owner = ownerID;
	proj->angle = angle;
	proj->marker = marker;
	if (speed)
		proj->speed = speed;
	if (rotaSpeed)
		proj->rotaSpeed = rotaSpeed;
	if (accel)
		proj->acceleration = accel;
	return (proj);
}

void	pushProjectile(Projectile *proj, lua_State *Lua)
{
	Projectile	**a = lua_newuserdata(Lua, sizeof(proj));

	luaL_getmetatable(Lua, "projectile");
	lua_setmetatable(Lua, -2);
	*a = proj;
}

void	pushCharacter(lua_State *Lua, Character *character)
{
	Character	**a = lua_newuserdata(Lua, sizeof(character));

	luaL_getmetatable(Lua, "character");
	lua_setmetatable(Lua, -2);
	*a = character;
}

int	playSound(char const *path, bool freeAll)
{
	static	sfSound		*musics[16];
	static	sfSoundBuffer	*buffers[16];
	static	char		*paths[16];
	static	bool		first = true;

	if (first) {
		first = false;
		memset(buffers, 0, sizeof(musics));
		for (int i = 0; i < 16; i++)
			musics[i] = sfSound_create();
		memset(paths, 0, sizeof(paths));
	}
	if (freeAll) {
		for (int i = 0; i < 16; i++) {
			if (paths[i]) {
				free(paths[i]);
				sfSound_destroy(musics[i]);
				sfSoundBuffer_destroy(buffers[i]);
			}
		}
		return (0);
	}
	for (int i = 0; i < 16; i++) {
		if (!paths[i]) {
			buffers[i] = sfSoundBuffer_createFromFile(path);
			if (!buffers[i])
				return (1);
			paths[i] = strdup(path);
			sfSound_setBuffer(musics[i], buffers[i]);
			sfSound_setVolume(musics[i], game.settings.sfxVolume);
			sfSound_play(musics[i]);
			return (0);
		} else if(strcmp(paths[i], path) == 0 && sfSound_getStatus(musics[i]) != sfPlaying) {
			sfSound_setPlayingOffset(musics[i], (sfTime){0});
			sfSound_setVolume(musics[i], game.settings.sfxVolume);
			sfSound_play(musics[i]);
			return (0);
		}
	}
	for (int i = 0; i < 16; i++) {
		if(sfSound_getStatus(musics[i]) != sfPlaying) {
			sfSoundBuffer	*buffer;

			buffer = sfSoundBuffer_createFromFile(path);
			if (!buffer)
				return (1);
			sfSoundBuffer_destroy(buffers[i]);
			sfSound_setBuffer(musics[i], buffer);
			sfSound_setVolume(musics[i], game.settings.sfxVolume);
			buffers[i] = buffer;
			free(paths[i]);
			paths[i] = strdup(path);
			sfSound_play(musics[i]);
			return (0);
		}
	}
	return (2);
}

int	playSoundLua(lua_State *Lua)
{
	int	err;
	int	arg = lua_tonumber(Lua, 1);

	if (lua_isnumber(Lua, 1)) {
		if (arg < 0 || arg > game.sfx.length) {
			lua_pushboolean(Lua, false);
			lua_pushstring(Lua, "index out of range");
			return (2);
		} else if (((sfMusic **)game.sfx.content)[arg]) {
			sfMusic_play(((sfMusic **)game.sfx.content)[arg]);
			lua_pushboolean(Lua, true);
			return (1);
		}
	}
	err = playSound(luaL_checkstring(Lua, 1), false);
	if (!err) {
		lua_pushboolean(Lua, true);
		return (1);
	} else if (err == 1) {
		lua_pushboolean(Lua, false);
		lua_pushstring(Lua, "cannot load file");
		return (2);
	} else if (err == 2) {
		lua_pushboolean(Lua, false);
		lua_pushstring(Lua, "all voices are used");
		return (2);
	}
	lua_pushboolean(Lua, false);
	lua_pushstring(Lua, "unknown error");
	return (2);
}

int	destroyProjectile(lua_State *Lua)
{
	Projectile	**proj = luaL_checkudata(Lua, 1, "projectile");

	luaL_argcheck(Lua, proj != NULL, 1, "'projectile' expected");
	(*proj)->toRemove = true;
	*proj = NULL;
	return (0);
}

int	getCharacterIndex(char const *test)
{
	if (strcmp(test, "animation") == 0)
		return (1);
	else if (strcmp(test, "x") == 0)
		return (2);
	else if (strcmp(test, "y") == 0)
		return (3);
	else if (strcmp(test, "name") == 0)
		return (4);
	return (0);
}

int	setCharacterField(lua_State *Lua)
{
	Character	**character = luaL_checkudata(Lua, 1, "character");
	char	const	*buffer;
	int		index = lua_isnumber(Lua, 2) ? luaL_checknumber(Lua, 2) : getCharacterIndex(luaL_checkstring(Lua, 2));

	luaL_argcheck(Lua, character != NULL, 1, "'character' expected");
	if (!*character)
		luaL_error(Lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		(*character)->movement.animation = luaL_checknumber(Lua, 3);
		break;
	case 2:
		(*character)->movement.pos.x = luaL_checknumber(Lua, 3);
		break;
	case 3:
		(*character)->movement.pos.y = luaL_checknumber(Lua, 3);
		break;
	case 4:
		buffer = luaL_checkstring(Lua, 3);
		if (strlen(buffer) >= sizeof((*character)->name))
			luaL_error(Lua, "Max length for the name is %i but given one has %i characters", strlen(buffer), sizeof((*character)->name));
		strcpy((*character)->name, buffer);
		break;
	default:
		luaL_error(Lua, "This index is in read-only");
	}
	return (0);
}

int	getCharacterField(lua_State *Lua)
{
	Character	**character = luaL_checkudata(Lua, 1, "character");
	char	const	*ind = !lua_isnumber(Lua, 2) ? luaL_checkstring(Lua, 2) : NULL;
	int		index = lua_isnumber(Lua, 2) ? luaL_checknumber(Lua, 2) : getCharacterIndex(ind);

	luaL_argcheck(Lua, character != NULL, 1, "'character' expected");
	if (!*character)
		luaL_error(Lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		lua_pushnumber(Lua, (*character)->movement.animation);
		break;
	case 2:
		lua_pushnumber(Lua, (*character)->movement.pos.x);
		break;
	case 3:
		lua_pushnumber(Lua, (*character)->movement.pos.y);
		break;
	case 4:
		lua_pushstring(Lua, (*character)->name);
		break;
	default:
		for (int i = 0; ind && character_lib[i].name; i++) {
			if (strcmp(character_lib[i].name, ind) == 0) {
				lua_pushcfunction(Lua, character_lib[i].func);
				return (1);
			}
		}
		lua_pushnil(Lua);
	}
	return (1);
}

int	getProjectileIndex(char const *test)
{
	if (strcmp(test, "bankId") == 0)
		return (1);
	else if (strcmp(test, "x") == 0)
		return (2);
	else if (strcmp(test, "y") == 0)
		return (3);
	else if (strcmp(test, "speed") == 0)
		return (4);
	else if (strcmp(test, "acceleration") == 0)
		return (5);
	else if (strcmp(test, "owner") == 0)
		return (6);
	else if (strcmp(test, "angle") == 0)
		return (7);
	else if (strcmp(test, "rotationSpeed") == 0)
		return (8);
	else if (strcmp(test, "maxSpeed") == 0)
		return (9);
	else if (strcmp(test, "minSpeed") == 0)
		return (10);
	else if (strcmp(test, "lifeTime") == 0)
		return (11);
	return (0);
}

int	setProjectileField(lua_State *Lua)
{
	Projectile	**proj = luaL_checkudata(Lua, 1, "projectile");
	int		index = lua_isnumber(Lua, 2) ? luaL_checknumber(Lua, 2) : getProjectileIndex(luaL_checkstring(Lua, 2));

	luaL_argcheck(Lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(Lua, "Trying to access deleted object");
	switch (index) {
	case 2:
		(*proj)->pos.x = luaL_checknumber(Lua, 3);
		break;
	case 3:
		(*proj)->pos.y = luaL_checknumber(Lua, 3);
		break;
	case 4:
		(*proj)->speed = luaL_checknumber(Lua, 3);
		break;
	case 5:
		(*proj)->acceleration = luaL_checknumber(Lua, 3);
		break;
	case 7:
		(*proj)->angle = luaL_checknumber(Lua, 3);
		break;
	case 8:
		(*proj)->rotaSpeed = luaL_checknumber(Lua, 3);
		break;
	default:
		luaL_error(Lua, "This index is in read-only");
	}
	return (0);
}

int	getProjectileField(lua_State *Lua)
{
	Projectile	**proj = luaL_checkudata(Lua, 1, "projectile");
	char	const	*ind = !lua_isnumber(Lua, 2) ? luaL_checkstring(Lua, 2) : NULL;
	int		index = lua_isnumber(Lua, 2) ? luaL_checknumber(Lua, 2) : getProjectileIndex(ind);

	luaL_argcheck(Lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(Lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		lua_pushnumber(Lua, (*proj)->bankID);
		break;
	case 2:
		lua_pushnumber(Lua, (*proj)->pos.x);
		break;
	case 3:
		lua_pushnumber(Lua, (*proj)->pos.y);
		break;
	case 4:
		lua_pushnumber(Lua, (*proj)->speed);
		break;
	case 5:
		lua_pushnumber(Lua, (*proj)->acceleration);
		break;
	case 6:
		lua_pushnumber(Lua, (*proj)->owner);
		break;
	case 7:
		lua_pushnumber(Lua, (*proj)->angle);
		break;
	case 8:
		lua_pushnumber(Lua, (*proj)->rotaSpeed);
		break;
	case 9:
		lua_pushnumber(Lua, (*proj)->maxSpeed);
		break;
	case 10:
		lua_pushnumber(Lua, (*proj)->minSpeed);
		break;
	case 11:
		lua_pushnumber(Lua, sfTime_asSeconds(sfClock_getElapsedTime((*proj)->clock)));
		break;
	default:
		for (int i = 0; ind && projectiles_lib[i].name; i++) {
			if (strcmp(projectiles_lib[i].name, ind) == 0) {
				lua_pushcfunction(Lua, projectiles_lib[i].func);
				return (1);
			}
		}
		lua_pushnil(Lua);
	}
	return (1);
}

int	stopTime(lua_State *Lua)
{
	if (!lua_isboolean(Lua, 1))
		luaL_error(Lua, "Invalid argument #1 to 'stopTime': Expected boolean, got %s", lua_typename(Lua, lua_type(Lua, 1)));
	game.battle_infos.timeStopped = lua_toboolean(Lua, 1);
	return 0;
}

int	getElapsedTime(lua_State *Lua)
{
	lua_pushnumber(Lua, sfTime_asSeconds(sfClock_getElapsedTime(game.battle_infos.clock)));
	return 1;
}

int	addProjectileLua(lua_State *Lua)
{
	double		x		= luaL_checknumber(Lua, 1);
	double		y		= luaL_checknumber(Lua, 2);
	double		projID		= luaL_checknumber(Lua, 3);
	double		ownerID		= luaL_checknumber(Lua, 4);
	double		angle		= luaL_checknumber(Lua, 5);
	double		speed		= lua_isnone(Lua, 6) ? 0 : luaL_checknumber(Lua, 6);
	double		rotaSpeed	= lua_isnone(Lua, 7) ? 0 : luaL_checknumber(Lua, 7);
	double		accel		= lua_isnone(Lua, 8) ? 0 : luaL_checknumber(Lua, 8);
	double		marker		= lua_isnone(Lua, 9) ? 0 : luaL_checknumber(Lua, 9);
	Projectile	*proj;

	if (projID >= game.battle_infos.projectileBank.length || projID < 0) {
		lua_pushnil(Lua);
		lua_pushstring(Lua, "index out of bank range");
	        return 2;
	}
	proj = addProjectile(projID, x, y, ownerID, angle, speed, rotaSpeed, accel, marker);
	if (!proj)
		luaL_error(Lua, "Out of memory");
	pushProjectile(proj, Lua);
	return 1;
}

int	yield(lua_State *Lua)
{
	int	frames = lua_isnone(Lua, 1) ? 1 : luaL_checknumber(Lua, 1);

	game.battle_infos.yieldTime = frames;
	if (frames <= 0)
		return 0;
	return lua_yield(Lua, 0);
}
