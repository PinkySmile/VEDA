#include "configParser.h"
#include <malloc.h>
#include <concatf.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int	isInString(char c, char *str);

char	*transformString(char *str, int length, ParserInfos *infos)
{
	char	*result = strdup("");
	char	*buffer = NULL;

	for (int i = 0; i < length; i++) {
		buffer = result;
		if (isInString(str[i], infos->strChar) != -1)
			result = concatf("%s\\%c", result, str[i]);
		else if (str[i] >= ' ' && str[i] != 127)
			result = concatf("%s%c", result, str[i]);
		else if (str[i] == '\n')
			result = concatf("%s\\n", result);
		else if (str[i] == '\r')
			result = concatf("%s\\r", result);
		else if (str[i] == '\a')
			result = concatf("%s\\a", result);
		else if (str[i] == '\b')
			result = concatf("%s\\b", result);
		else if (str[i] == '\v')
			result = concatf("%s\\v", result);
		else if (str[i] == '\t')
			result = concatf("%s\\t", result);
		else if (str[i] == '\f')
			result = concatf("%s\\f", result);
		else if (str[i] == '\e')
			result = concatf("%s\\e", result);
		else if (str[i] == '\0')
			result = concatf("%s\\x00", result);
		else
			result = concatf("%s\\x%s%x", result, str[i] > 15 ? "" : "0", str[i]);
		free(buffer);
	}
	return (result);
}

char	*dataToString(void *data, ParserTypes type, ParserInfos *infos, int indentation)
{
	char	*indent = strdup("");
	char	*index = NULL;
	char	*result = NULL;
	char	*buffer = NULL;

	for (int i = 0; i < indentation; i++)
		indent = concat(indent, "\t", true, false);
	switch(type) {
	case ParserBooleanType:
		result = strdup(*(ParserBoolean *)data ? "true" : "false");
		break;
	case ParserStringType:
		buffer = transformString(((ParserString *)data)->content, ((ParserString *)data)->length, infos);
		result = concatf("%c%s%c", infos->strChar[0], buffer, infos->strChar[0]);
		free(buffer);
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
	case ParserObjType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->objOpen;
		result[1] = 0;
		for (ParserObj *list = data; list; list = list->next) {
			buffer = result;
			index = transformString(list->index, strlen(list->index), infos);
			if (!infos->compact)
				result = concatf("%s\n%s\t%c%s%c%c ", result, indent, infos->strChar[0], index, infos->strChar[0], infos->eqChar);
			else
				result = concatf("%s%c%s%c%c", result, infos->strChar[0], list->index, infos->strChar[0], infos->eqChar);
			free(index);
			free(buffer);
			if (!result)
				return (NULL);
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
		result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->objClose);
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
	case ParserNullType:
		result = strdup("null");
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
	int	fd;
	bool	success = true;
	char	*buffer = NULL;

	buffer = Parser_createString(data, type, infos);
	remove(path);
	fd = open(path, O_WRONLY | O_CREAT, 0664);
	if (fd < 0)
		return (false);
	if (!buffer)
		return (false);
	success = write(fd, buffer, strlen(buffer)) == (int)strlen(buffer);
	free(buffer);
	close(fd);
	return (success);
}
