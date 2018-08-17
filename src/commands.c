#include "structs.h"
#include "concatf.h"
#include <string.h>

CommandInfos	executeCommand(char *cmd, char *args)
{
	CommandInfos	output;

	memset(&output, 0, sizeof(output));
	if (strcmp(cmd, "") == 0) {
		output.stderror = strdup("%");
		output.returnValue = 0;
	} else {
		output.stderror = concatf("'%s': Command not found", cmd);
		output.returnValue = 127;
	}
	return (output);
}