#include <string.h>
#include <malloc.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "structs.h"

extern	const	luaL_Reg	character_lib[];

int	char2string(lua_State *lua)
{
	Character	**proj = luaL_checkudata(lua, 1, "character");

	luaL_argcheck(lua, proj != NULL, 1, "'character' expected");
	lua_pushfstring(lua, "character ('%s')", (*proj)->name);
	return 1;
}

void	pushCharacter(lua_State *lua, Character *character)
{
	Character	**a = lua_newuserdata(lua, sizeof(character));

	luaL_getmetatable(lua, "character");
	lua_setmetatable(lua, -2);
	*a = character;
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
	else if (strcmp(test, "id") == 0)
		return (5);
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
			strcpy((char *)(*character)->name, buffer);
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
	int		charID = -1;

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
			lua_pushstring(lua, (char *)(*character)->name);
			break;
		case 5:
			for (int i = 0; i < game.state.characters.length; i++)
				if (getCharacter(i) == *character) {
					charID = i;
					break;
				}
			lua_pushnumber(lua, charID);
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
