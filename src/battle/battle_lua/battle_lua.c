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
#include "battle_lua.h"

extern	const	luaL_Reg	projectiles_lib[];
extern	const	luaL_Reg	character_lib[];

Projectile	*addProjectile(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker)
{
	Projectile	*bank = game.state.battle_infos.projectileBank.content;
	Projectile	*proj;
	list_t		*list = &game.state.battle_infos.projectiles;

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
	if (!proj) {
		if (list->prev) {
			list->prev->next = NULL;
			free(list);
		}
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

void	pushProjectile(Projectile *proj, lua_State *lua)
{
	Projectile	**a = lua_newuserdata(lua, sizeof(proj));

	luaL_getmetatable(lua, "projectile");
	lua_setmetatable(lua, -2);
	*a = proj;
}

void	pushCharacter(lua_State *lua, Character *character)
{
	Character	**a = lua_newuserdata(lua, sizeof(character));

	luaL_getmetatable(lua, "character");
	lua_setmetatable(lua, -2);
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

int	playSoundLua(lua_State *lua)
{
	int	err;
	int	arg = lua_tonumber(lua, 1);

	if (lua_isnumber(lua, 1)) {
		if (arg < 0 || arg > game.ressources.sfx.length) {
			lua_pushboolean(lua, false);
			lua_pushstring(lua, "index out of range");
			return (2);
		} else if (((sfMusic **)game.ressources.sfx.content)[arg]) {
			sfMusic_play(((sfMusic **)game.ressources.sfx.content)[arg]);
			lua_pushboolean(lua, true);
			return (1);
		}
	}
	err = playSound(luaL_checkstring(lua, 1), false);
	if (!err) {
		lua_pushboolean(lua, true);
		return (1);
	} else if (err == 1) {
		lua_pushboolean(lua, false);
		lua_pushstring(lua, "cannot load file");
		return (2);
	} else if (err == 2) {
		lua_pushboolean(lua, false);
		lua_pushstring(lua, "all voices are used");
		return (2);
	}
	lua_pushboolean(lua, false);
	lua_pushstring(lua, "unknown error");
	return (2);
}

int	destroyProjectile(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
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

int	setCharacterField(lua_State *lua)
{
	Character	**character = luaL_checkudata(lua, 1, "character");
	char	const	*buffer;
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getCharacterIndex(luaL_checkstring(lua, 2));

	luaL_argcheck(lua, character != NULL, 1, "'character' expected");
	if (!*character)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		(*character)->movement.animation = luaL_checknumber(lua, 3);
		break;
	case 2:
		(*character)->movement.pos.x = luaL_checknumber(lua, 3);
		break;
	case 3:
		(*character)->movement.pos.y = luaL_checknumber(lua, 3);
		break;
	case 4:
		buffer = luaL_checkstring(lua, 3);
		if (strlen(buffer) >= sizeof((*character)->name))
			luaL_error(lua, "Max length for the name is %i but given one has %i characters", strlen(buffer), sizeof((*character)->name));
		strcpy((*character)->name, buffer);
		break;
	default:
		luaL_error(lua, "This index is in read-only");
	}
	return (0);
}

int	getCharacterField(lua_State *lua)
{
	Character	**character = luaL_checkudata(lua, 1, "character");
	char	const	*ind = !lua_isnumber(lua, 2) ? luaL_checkstring(lua, 2) : NULL;
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getCharacterIndex(ind);

	luaL_argcheck(lua, character != NULL, 1, "'character' expected");
	if (!*character)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		lua_pushnumber(lua, (*character)->movement.animation);
		break;
	case 2:
		lua_pushnumber(lua, (*character)->movement.pos.x);
		break;
	case 3:
		lua_pushnumber(lua, (*character)->movement.pos.y);
		break;
	case 4:
		lua_pushstring(lua, (*character)->name);
		break;
	default:
		for (int i = 0; ind && character_lib[i].name; i++) {
			if (strcmp(character_lib[i].name, ind) == 0) {
				lua_pushcfunction(lua, character_lib[i].func);
				return (1);
			}
		}
		lua_pushnil(lua);
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

int	setProjectileField(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getProjectileIndex(luaL_checkstring(lua, 2));

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
	case 2:
		(*proj)->pos.x = luaL_checknumber(lua, 3);
		break;
	case 3:
		(*proj)->pos.y = luaL_checknumber(lua, 3);
		break;
	case 4:
		(*proj)->speed = luaL_checknumber(lua, 3);
		break;
	case 5:
		(*proj)->acceleration = luaL_checknumber(lua, 3);
		break;
	case 7:
		(*proj)->angle = luaL_checknumber(lua, 3);
		break;
	case 8:
		(*proj)->rotaSpeed = luaL_checknumber(lua, 3);
		break;
	default:
		luaL_error(lua, "This index is in read-only");
	}
	return (0);
}

int	getProjectileField(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");
	char	const	*ind = !lua_isnumber(lua, 2) ? luaL_checkstring(lua, 2) : NULL;
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getProjectileIndex(ind);

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
	case 1:
		lua_pushnumber(lua, (*proj)->bankID);
		break;
	case 2:
		lua_pushnumber(lua, (*proj)->pos.x);
		break;
	case 3:
		lua_pushnumber(lua, (*proj)->pos.y);
		break;
	case 4:
		lua_pushnumber(lua, (*proj)->speed);
		break;
	case 5:
		lua_pushnumber(lua, (*proj)->acceleration);
		break;
	case 6:
		lua_pushnumber(lua, (*proj)->owner);
		break;
	case 7:
		lua_pushnumber(lua, (*proj)->angle);
		break;
	case 8:
		lua_pushnumber(lua, (*proj)->rotaSpeed);
		break;
	case 9:
		lua_pushnumber(lua, (*proj)->maxSpeed);
		break;
	case 10:
		lua_pushnumber(lua, (*proj)->minSpeed);
		break;
	case 11:
		lua_pushnumber(lua, sfTime_asSeconds(sfClock_getElapsedTime((*proj)->clock)));
		break;
	default:
		for (int i = 0; ind && projectiles_lib[i].name; i++) {
			if (strcmp(projectiles_lib[i].name, ind) == 0) {
				lua_pushcfunction(lua, projectiles_lib[i].func);
				return (1);
			}
		}
		lua_pushnil(lua);
	}
	return (1);
}

int	stopTime(lua_State *lua)
{
	if (!lua_isboolean(lua, 1))
		luaL_error(lua, "Invalid argument #1 to 'stopTime': Expected boolean, got %s", lua_typename(lua, lua_type(lua, 1)));
	game.state.battle_infos.timeStopped = lua_toboolean(lua, 1);
	return 0;
}

int	getElapsedTime(lua_State *lua)
{
	lua_pushnumber(lua, sfTime_asSeconds(sfClock_getElapsedTime(game.state.battle_infos.clock)));
	return 1;
}

int	addProjectileLua(lua_State *lua)
{
	double		x		= luaL_checknumber(lua, 1);
	double		y		= luaL_checknumber(lua, 2);
	double		projID		= luaL_checknumber(lua, 3);
	double		ownerID		= luaL_checknumber(lua, 4);
	double		angle		= luaL_checknumber(lua, 5);
	double		speed		= lua_isnone(lua, 6) ? 0 : luaL_checknumber(lua, 6);
	double		rotaSpeed	= lua_isnone(lua, 7) ? 0 : luaL_checknumber(lua, 7);
	double		accel		= lua_isnone(lua, 8) ? 0 : luaL_checknumber(lua, 8);
	double		marker		= lua_isnone(lua, 9) ? 0 : luaL_checknumber(lua, 9);
	Projectile	*proj;

	if (projID >= game.state.battle_infos.projectileBank.length || projID < 0) {
		lua_pushnil(lua);
		lua_pushstring(lua, "index out of bank range");
	        return 2;
	}
	proj = addProjectile(projID, x, y, ownerID, angle, speed, rotaSpeed, accel, marker);
	if (!proj)
		luaL_error(lua, "Out of memory");
	pushProjectile(proj, lua);
	return 1;
}

int	yield(lua_State *lua)
{
	int	frames = lua_isnone(lua, 1) ? 1 : luaL_checknumber(lua, 1);

	game.state.battle_infos.yieldTime = frames;
	if (frames <= 0)
		return 0;
	return lua_yield(lua, 0);
}
