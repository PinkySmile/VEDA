#include <lua.h>
#include "structs.h"

void	destroyDialogs()
{
	if (game.resources.dialogLuaScript)
		lua_close(game.resources.dialogLuaScript);
}