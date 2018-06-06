#include "configParser.h"
#include <malloc.h>

char	*ParserString_toCharStar(ParserString *value)
{
	return (value->content);
}

void	ParserString_destroy(ParserString *value)
{
	free(value->content);
	free(value);
}