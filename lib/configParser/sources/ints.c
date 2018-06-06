#include "configParser.h"
#include <malloc.h>

int	ParserInt_toInt(ParserInt *value)
{
	return (*value);
}

void	ParserInt_destroy(ParserInt *value)
{
	free(value);
}