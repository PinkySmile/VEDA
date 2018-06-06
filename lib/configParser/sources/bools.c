#include "configParser.h"
#include <malloc.h>

bool	ParserBoolean_toBool(ParserBoolean *value)
{
	return (*value);
}

void	ParserBoolean_destroy(ParserBoolean *value)
{
	free(value);
}