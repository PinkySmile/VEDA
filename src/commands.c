#include "structs.h"
#include "concatf.h"
#include <string.h>

char	*executeCommand(char *cmd, char **args)
{
	if (strcmp(cmd, "") == 0)
		return (strdup("%"));
	else
		return concatf("'%s': Command not found", cmd);
	return (NULL);
}