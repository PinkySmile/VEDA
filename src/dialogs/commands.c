#include <string.h>
#include <malloc.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"

char	*executeCommand(char *cmd, char **args)
{
	if (strcmp(cmd, "") == 0)
		return (strdup("%"));
	return concatf("'%s': Command not found", cmd);
}

bool	addStringToDialogBox(char *str, char **resulting)
{
	char	*buffer;
	size_t	len = strlen(*resulting);

	if (!str)
		return (addStringToDialogBox("(null)", resulting));
	buffer = realloc(resulting, len + strlen(str) + 1);
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

	for (diag->index++; diag->rawText[diag->index] && diag->rawText[diag->index] != '%'; diag->index++);
	if (!diag->rawText[diag->index]) {
		addStringToDialogBox("Unfinished command found", &diag->displayedText);
		return;
	}
	diag->rawText[diag->index] = 0;
	result = executeCommand(command, NULL);
	if (result)
		addStringToDialogBox(result, &diag->displayedText);
	free(result);
	diag->rawText[diag->index] = '%';
	diag->index++;
}