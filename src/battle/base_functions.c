#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <utils.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "battle_lua.h"

int	playSound(char const *path, bool freeAll)
{
	static	sfSound		*musics[SOUNDS_BUFFER_SIZE];
	static	sfSoundBuffer	*buffers[SOUNDS_BUFFER_SIZE];
	static	char		*paths[SOUNDS_BUFFER_SIZE];
	static	bool		first = true;

	if (first) {
		first = false;
		memset(buffers, 0, sizeof(buffers));
		for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++)
			musics[i] = sfSound_create();
		memset(paths, 0, sizeof(paths));
	}
	if (freeAll) {
		for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) {
			if (paths[i]) {
				free(paths[i]);
				sfSoundBuffer_destroy(buffers[i]);
			}
			sfSound_destroy(musics[i]);
		}
		return (0);
	}
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) {
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
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) {
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
		if (!getSoundEffect(arg)) {
			lua_pushnil(lua);
			lua_pushstring(lua, "index out of range");
			return (2);
		} else if (getSoundEffect(arg)) {
			playSoundEffect(getSoundEffect(arg));
			lua_pushboolean(lua, true);
			return (1);
		}
	}
	err = playSound(luaL_checkstring(lua, 1), false);
	if (!err) {
		lua_pushboolean(lua, true);
		return (1);
	} else if (err == 1) {
		lua_pushnil(lua);
		lua_pushstring(lua, "cannot load file");
		return (2);
	} else if (err == 2) {
		lua_pushnil(lua);
		lua_pushstring(lua, "all voices are used");
		return (2);
	}
	lua_pushnil(lua);
	lua_pushstring(lua, "unknown error");
	return (2);
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

int	yield(lua_State *lua)
{
	int	frames = lua_isnone(lua, 1) ? 1 : luaL_checknumber(lua, 1);

	game.state.battle_infos.yieldTime = frames;

	if (frames <= 0)
		return 0;
	return lua_yield(lua, 0);
}
