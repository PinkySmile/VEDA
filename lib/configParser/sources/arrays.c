#include "configParser.h"
#include <malloc.h>

void	*ParserArray_getElement(ParserArray *array, int index)
{
	int	step = 0;

	if (index < 0 || index >= array->length)
		return (NULL);
	step = getSizeOf(array->type);
	return (array->content + step * index);
}

void	ParserArray_destroy(ParserArray *array)
{
	free(array->content);
}