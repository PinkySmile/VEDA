#ifndef __BATTLE_API_H_
#define __BATTLE_API_H_

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

bool	addProjectile(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker);
int	addProjectileLua(lua_State *Lua);
int	playSoundLua(lua_State *Lua);
int	getElapsedTime(lua_State *Lua);
int	stopTime(lua_State *Lua);
int	yield(lua_State *Lua);

#endif
