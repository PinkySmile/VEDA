#include "configParser.h"
#include <malloc.h>

void	*copyData(void *data, ParserTypes type)
{
	int	size = getSizeOf(type);
	void	*new = malloc(size);

	if (new) {
		for (int i = 0; i < size; i++)
			((char *)new)[i] = ((char *)data)[i];
		if (type == ParserObjType && ((ParserObj *)data)->next)
			((ParserObj *)data)->next->prev = new;
		else if (type == ParserListType && ((ParserList *)data)->next)
			((ParserList *)data)->next->prev = new;
	}
	return (new);
}

char	*typeToString(ParserTypes type)
{
	char	*name = "Unknown";

	switch(type) {
	case ParserBooleanType:
		name = "boolean";
		break;
	case ParserStringType:
		name = "string";
		break;
	case ParserFloatType:
		name = "float";
		break;
	case ParserArrayType:
		name = "array";
		break;
	case ParserObjType:
		name = "object";
		break;
	case ParserListType:
		name = "list";
		break;
	case ParserIntType:
		name = "int";
		break;
	case ParserNullType:
		name = "null";
		break;
	}
	return (name);
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
	case ParserObjType:
		size = sizeof(ParserObj);
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
	case ParserObjType:
		ParserObj_destroy(data);
		break;
	case ParserListType:
		ParserList_destroy(data);
		break;
	case ParserIntType:
		ParserInt_destroy(data);
		break;
	}
}
