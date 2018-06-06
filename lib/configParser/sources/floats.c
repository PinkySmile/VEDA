#include "configParser.h"
#include <malloc.h>

float	ParserFloat_toFloat(ParserFloat *value)
{
	return (*value);
}

void	ParserFloat_destroy(ParserFloat *value)
{
	free(value);
}