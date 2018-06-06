#include "configParser.h"
#include <malloc.h>
#include <stdio.h>

void	Parser_printElement(void *data, ParserTypes type, ParserInfos *infos)
{
	char	*result = Parser_createString(data, type, infos ? infos : JSON_NOT_COMPACT);
	
	printf("%s\n", result);
	free(result);
}