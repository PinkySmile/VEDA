#include "configParser.h"
#include <malloc.h>
#include <concatf.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char	*dataToString(void *data, ParserTypes type, ParserInfos *infos, int indentation)
{
	char	*indent = strdup("");
	char	*result = NULL;
	char	*buffer = NULL;

	for (int i = 0; i < indentation; i++)
		indent = concat(indent, "\t", true, false);
	switch(type) {
	case ParserBooleanType:
		result = strdup(*(ParserBoolean *)data ? "true" : "false");
		break;
	case ParserStringType:
		result = concatf("%c%s%c", infos->strChar[0], ((ParserString *)data)->content, infos->strChar[0]);
		break;
	case ParserFloatType:
		result = concatf("%f", *(ParserFloat *)data);
		break;
	case ParserArrayType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->arrOpen;
		result[1] = 0;
		for (int i = 0; i < ((ParserArray *)data)->length; i++) {
			if (!infos->compact) {
				buffer = result;
				result = concatf("%s\n%s\t", result, indent);
				if (!result)
					return (NULL);
				free(buffer);
			}
			result = concat(result, dataToString(ParserArray_getElement(data, i), ((ParserArray *)data)->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->arrClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case ParserDictType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->dictOpen;
		result[1] = 0;
		for (ParserDict *list = data; list; list = list->next) {
			if (!infos->compact) {
				buffer = result;
				result = concatf("%s\n%s\t%c%s%c%c ", result, indent, infos->strChar[0], list->index, infos->strChar[0], infos->eqChar);
				if (!result)
					return (NULL);
				free(buffer);
			} else {
				buffer = result;
				result = concatf("%s%c%s%c%c", result, infos->strChar[0], list->index, infos->strChar[0], infos->eqChar);
				if (!result)
					return (NULL);
				free(buffer);
			}
			result = concat(result, dataToString(list->data, list->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->dictClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case ParserListType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->arrOpen;
		result[1] = 0;
		for (ParserList *list = data; list; list = list->next) {
			if (!infos->compact) {
				buffer = result;
				result = concatf("%s\n%s\t", result, indent);
				if (!result)
					return (NULL);
				free(buffer);
			}
			result = concat(result, dataToString(list->data, list->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->arrClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case ParserIntType:
		result = concatf("%i", *(ParserInt *)data);
		break;
	}
	free(indent);
	return (result);
}

char	*Parser_createString(void *data, ParserTypes type, ParserInfos *infos)
{
	if (infos && !strlen(infos->strChar))
		return (NULL);
	return (dataToString(data, type, infos ? infos : JSON_COMPACT, 0));
}

bool	Parser_createFile(char *path, void *data, ParserTypes type, ParserInfos *infos)
{
	int	fd = open(path, O_WRONLY | O_CREAT, 0664);
	bool	success = true;
	char	*buffer = NULL;

	if (fd < 0)
		return (false);
	buffer = Parser_createString(data, type, infos);
	if (!buffer)
		return (false);
	success = write(fd, buffer, strlen(buffer)) == (int)strlen(buffer);
	close(fd);
	return (success);
}