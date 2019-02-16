#include <string.h>
#include <malloc.h>
#include <utils.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"

const	char	*callLuaFunction(lua_State *lua, char *name, char **args)
{
	int	nbArgs = 0;

	lua_getglobal(lua, name);
	for (; args[nbArgs]; nbArgs++)
		lua_pushstring(lua, args[nbArgs]);
	lua_pcall(lua, nbArgs, 1, 0);
	return lua_tostring(lua, -1);
}

char	*executeCommand(char *cmd, char **args)
{
	if (strcmp(cmd, "") == 0)
		return (strdup("%"));
	if (strcmp(cmd, "lua") == 0) {
		if (!*args)
			return (strdup("Expected 1 argument (function name)"));
		if (!game.resources.dialogLuaScript)
			return (strdup("The dialog script has not been loaded"));
		return strdup(callLuaFunction(game.resources.dialogLuaScript, *args, &args[1]));
	}
	return concatf("'%s': Command not found", cmd);
}

bool	addStringToDialogBox(char *str, char **resulting)
{
	char	*buffer;
	size_t	len = strlen(*resulting);

	if (!str)
		return (addStringToDialogBox("(null)", resulting));
	buffer = realloc(*resulting, len + strlen(str) + 1);
	if (!buffer)
		return (false);
	memset(&buffer[len], 0, strlen(str) + 1);
	*resulting = buffer;
	for (int i = 0; str[i]; i++)
		if (!addCharacter(str[i], resulting, false))
			return (false);
	return (true);
}

void	resolveCommand(DialogDisplayed *diag)
{
	char	*command = &diag->rawText[diag->index + 1];
	char	*result;
	char	**args;

	for (diag->index++; diag->rawText[diag->index] && diag->rawText[diag->index] != '%'; diag->index++)
		if (diag->rawText[diag->index] == '\\')
			diag->index++;
	if (!diag->rawText[diag->index]) {
		addStringToDialogBox("Unfinished command found", &diag->displayedText);
		return;
	}
	diag->rawText[diag->index] = 0;
	args = split(command, ' ');
	command = args[0];
	args = &args[1];
	result = executeCommand(command, args);
	free(command);
	free(&args[-1]);
	if (result)
		addStringToDialogBox(result, &diag->displayedText);
	free(result);
	diag->rawText[diag->index] = '%';
	diag->index++;
}