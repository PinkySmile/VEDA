#include "configParser.h"
#include <stdlib.h>

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
	ParserList_destroy(array->list);
	free(array->content);
	free(array);
}