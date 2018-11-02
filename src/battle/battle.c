#include <lua.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <lualib.h>
#include <stdlib.h>
#include <lauxlib.h>
#include "utils.h"
#include "graphic.h"
#include "loading.h"
#include "display.h"
#include "concatf.h"
#include "structs.h"
#include "configs.h"
#include "loading.h"
#include "callbacks.h"
#include "functions.h"
#include "battle_lua.h"
#include "configParser.h"

int	proj2string(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	lua_pushfstring(lua, "projectile: %p", *proj);
	return 1;
}

int	char2string(lua_State *lua)
{
	Character	**proj = luaL_checkudata(lua, 1, "character");

	luaL_argcheck(lua, proj != NULL, 1, "'character' expected");
	lua_pushfstring(lua, "character ('%s')", (*proj)->name);
	return 1;
}

const luaL_Reg character_lib[] = {
	{"__index", getCharacterField},
	{"__newindex", setCharacterField},
	{"__tostring", char2string},
	{NULL, NULL}
};

const luaL_Reg projectiles_lib[] = {
	{"setToRemove", destroyProjectile},
	{"__index", getProjectileField},
	{"__newindex", setProjectileField},
	{"__tostring", proj2string},
	{NULL, NULL}
};

const luaL_Reg game_api[] = {
	{"playSound", playSoundLua},
	{"yield", yield},
	{"stopTime", stopTime},
	{"addProjectile", addProjectileLua},
	{"getElapsedTime", getElapsedTime},
	{NULL, NULL}
};

void	addDependencies(lua_State *lua)
{
	luaL_openlibs(lua);

	luaL_newmetatable(lua, "projectile");
	lua_pushstring(lua, "__index");
	lua_pushvalue(lua, -2);
	lua_settable(lua, -3);
	luaL_setfuncs(lua, projectiles_lib, 0);

	luaL_newmetatable(lua, "character");
	lua_pushstring(lua, "__index");
	lua_pushvalue(lua, -2);
	lua_settable(lua, -3);
	luaL_setfuncs(lua, character_lib, 0);

	lua_newtable(lua);
	luaL_setfuncs(lua, game_api, 0);
	lua_setglobal(lua, "vedaApi");
}
