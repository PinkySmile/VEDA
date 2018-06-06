#include "configParser.h"
#include <malloc.h>

void	*copyData(void *data, int size)
{
	char	*new = malloc(size);
	
	if (new)
		for (int i = 0; i < size; i++)
			new[i] = ((char *)data)[i];
	return (new);
}

int	getSizeOf(ParserTypes type)
{
	int	size = 0;

	switch(type) {
	case ParserBooleanType:
		size = sizeof(ParserBoolean);
		break;
	case ParserStringType:
		size = sizeof(ParserString);
		break;
	case ParserFloatType:
		size = sizeof(ParserFloat);
		break;
	case ParserArrayType:
		size = sizeof(ParserArray);
		break;
	case ParserDictType:
		size = sizeof(ParserDict);
		break;
	case ParserListType:
		size = sizeof(ParserList);
		break;
	case ParserIntType:
		size = sizeof(ParserInt);
		break;
	}
	return (size);
}

void	Parser_destroyData(void *data, ParserTypes type)
{
	if (!data)
		return;
	switch(type) {
	case ParserBooleanType:
		ParserBoolean_destroy(data);
		break;
	case ParserStringType:
		ParserString_destroy(data);
		break;
	case ParserFloatType:
		ParserFloat_destroy(data);
		break;
	case ParserArrayType:
		ParserArray_destroy(data);
		break;
	case ParserDictType:
		ParserDict_destroy(data);
		break;
	case ParserListType:
		ParserList_destroy(data);
		break;
	case ParserIntType:
		ParserInt_destroy(data);
		break;
	}
}