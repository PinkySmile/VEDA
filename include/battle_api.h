#ifndef __BATTLE_API_H_
#define __BATTLE_API_H_

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

bool	addProjectile(int id, int x, int y);
int	getElapsedTime(lua_State *Lua);
int	yield(lua_State *Lua);

#endif