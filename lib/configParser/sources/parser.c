#include "configParser.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERROR_RESULT(message)	((ParserResult){NULL, 0, message})

void	cleanString(char *str, ParserInfos *infos)
{
	int	quote = -1;

	for (int i = 0; str[i]; i++) {
		while (quote == -1 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'))
			for (int j = i; str[j]; j++)
				str[j] = str[j + 1];
		if (quote != -1 && str[i] == infos->strChar[quote])
			quote = -1;
		else for (int j = 0; quote == -1 && infos->strChar[j]; j++) {
			if (infos->strChar[j] == str[i])
				quote = j;
		}
	}
}

int	isInString(char c, char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] == c)
			return (i);
	return (-1);
}

bool	isFloat(char *str, ParserInfos *infos)
{
	int	i = 0;

	for (; isdigit(str[i]); i++);
	if (i == 0)
		return (false);
	if (str[i] == '.')
		i++;
	for (; isdigit(str[i]); i++);
	return (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->dictClose);
}

bool	isNbr(char *str, ParserInfos *infos)
{
	int	i = 0;

	for (; isdigit(str[i]); i++);
	if (i == 0)
		return (false);
	return (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->dictClose);
}

bool	isBool(char *str, ParserInfos *infos)
{
	int	i = 0;
	bool	found = true;

	for (; i < 4; i++)
		if (str[i] != "true"[i]) {
			found = false;
			break;
		}
	if (!found) {
		found = true;
		for (i = 0; i < 5; i++)
			if (str[i] != "false"[i]) {
				found = false;
				break;
			}
	}
	return (found && (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->dictClose));
}

ParserResult	getValue(char *str, ParserInfos *infos)
{
	ParserResult	result;
	ParserResult	buff;
	int		index = 0;
	int		index2 = 0;
	ParserDict	*dict;
	ParserList	*list;
	int		arrlvl = 0;
	int		dictlvl = 0;

	memset(&result, 0, sizeof(result));
	if (!*str)
		return (ERROR_RESULT("Unexpected <EOF>"));
	if (*str == infos->dictOpen && isInString(str[1], infos->strChar) >= 0) {
		index = 1;
		result.type = ParserDictType;
		result.data = malloc(sizeof(ParserDict));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		dict = result.data;
		memset(dict, 0, sizeof(*dict));
		while (str[index] != infos->dictClose && str[index]) {
			if (isInString(str[index], infos->strChar) == -1) {
				ParserDict_destroy(result.data);
				return (ERROR_RESULT("Dict keys must be strings"));
			}
			for (index2 = index + 1; infos->strChar[isInString(str[index], infos->strChar)] != str[index2]; index2++) {
				if (!str[index2]) {
					ParserDict_destroy(result.data);
					return (ERROR_RESULT("Unfinished string found"));
				}
			}
			if (dict->data) {
				dict->next = malloc(sizeof(*dict->next));
				if (!dict->next) {
					ParserDict_destroy(result.data);
					return (ERROR_RESULT("Alloc error"));
				}
				memset(dict->next, 0, sizeof(*dict->next));
				dict->next->prev = dict;
				dict = dict->next;
			}
			dict->index = malloc(index2 - index);
			if (!dict->index) {
				ParserDict_destroy(result.data);
				return (ERROR_RESULT("Alloc error"));
			}
			memset(dict->index, 0, index2 - index - 1);
			strncpy(dict->index, &str[index + 1], index2 - index - 1);
			dict->index[index2 - index - 1] = 0;
			index = index2 + 1;
			if (str[index] != infos->eqChar) {
				ParserDict_destroy(result.data);
				printf("ParserError: Expected equal character after dict key '%s'\n", dict->index);
				return (ERROR_RESULT("Expected equal character after dict key"));
			}
			index++;
			buff = getValue(&str[index], infos);
			if (buff.error) {
				ParserDict_destroy(result.data);
				return (buff);
			}
			dict->data = buff.data;
			dict->type = buff.type;
			for (; str[index] && ((str[index] != infos->dictClose && str[index] != infos->separator) || arrlvl > 0 || dictlvl > 0); index++) {
				if (str[index] == infos->dictOpen)
					dictlvl++;
				else if (str[index] == infos->arrOpen)
					arrlvl++;
				else if (str[index] == infos->dictClose)
					dictlvl--;
				else if (str[index] == infos->arrClose)
					arrlvl--;
			}
			if (str[index] == infos->separator)
				index++;
		}
		if (!str[index]) {
			ParserDict_destroy(result.data);
			printf("ParserError: Unexpected '%c' before <EOF>\n", infos->dictClose);
			return (ERROR_RESULT("Unexpected <EOF>"));
		}
	} else if (*str == infos->arrOpen) {
		index = 1;
		result.type = ParserListType;
		result.data = malloc(sizeof(ParserList));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		list = result.data;
		memset(list, 0, sizeof(*list));
		while (str[index] != infos->arrClose && str[index]) {
			buff = getValue(&str[index], infos);
			if (buff.error) {
				ParserList_destroy(result.data);
				return (buff);
			}
			if (list->data) {
				list->next = malloc(sizeof(*list->next));
				if (!list->next) {
					ParserList_destroy(result.data);
					return (ERROR_RESULT("Alloc error"));
				}
				memset(list->next, 0, sizeof(*list->next));
				list->next->prev = list;
				list = list->next;
			}
			list->data = buff.data;
			list->type = buff.type;
			for (; str[index] && ((str[index] != infos->arrClose && str[index] != infos->separator) || arrlvl > 0 || dictlvl > 0); index++) {
				if (str[index] == infos->dictOpen)
					dictlvl++;
				else if (str[index] == infos->arrOpen)
					arrlvl++;
				else if (str[index] == infos->dictClose)
					dictlvl--;
				else if (str[index] == infos->arrClose)
					arrlvl--;
			}
			if (str[index] == infos->separator)
				index++;
		}
		if (!str[index]) {
			ParserList_destroy(result.data);
			printf("ParserError: Unexpected '%c' before <EOF>\n", infos->arrClose);
			return (ERROR_RESULT("Unexpected <EOF>"));
		}
	} else if (isNbr(str, infos)) {
		result.type = ParserIntType;
		result.data = malloc(sizeof(ParserInt));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		*(ParserInt *)result.data = atoi(str);
	} else if (isFloat(str, infos)) {
		result.type = ParserFloatType;
		result.data = malloc(sizeof(ParserFloat));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		*(ParserFloat *)result.data = atof(str);
	} else if (isInString(*str, infos->strChar) >= 0) {
		result.type = ParserStringType;
		for (index=  1; infos->strChar[isInString(str[0], infos->strChar)] != str[index]; index++)
			if (!str[index])
				return (ERROR_RESULT("Unfinished string found"));
		result.data = malloc(sizeof(ParserString));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		(*(ParserString *)result.data).content = malloc(index);
		if (!(*(ParserString *)result.data).content) {
			free(result.data);
			return (ERROR_RESULT("Alloc error"));
		}
		memset((*(ParserString *)result.data).content, 0, index - 1);
		strncpy((*(ParserString *)result.data).content, &str[1], index - 1);
		(*(ParserString *)result.data).content[index - 1] = 0;
		(*(ParserString *)result.data).length = index - 1;
		if (str[index + 1] != infos->separator && str[index + 1] != infos->dictClose && str[index + 1] != infos->arrClose) {
			ParserString_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after a string\n", str[index + 1]);
			return (ERROR_RESULT("Unexpected character found after a string"));
		}
	} else if (isBool(str, infos)) {
		result.type = ParserBooleanType;
		result.data = malloc(sizeof(ParserBoolean));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		*(ParserBoolean *)result.data = (*str == 't');
	} else {
		printf("ParserError: Unexpected character '%c'\n", *str);
		return (ERROR_RESULT("Unexpected character found"));
	}
	return (result);
}

ParserResult	Parser_parseString(char *string, ParserInfos *infos)
{
	ParserResult	result;

	string = strdup(string);
	if (!infos)
		infos = JSON_COMPACT;
	if (!string)
		return (ERROR_RESULT("Couldn't copy string"));
	cleanString(string, infos);
	result = getValue(string, infos);
	free(string);
	return (result);
}

ParserResult	Parser_parseFile(char *path, ParserInfos *infos)
{
	int		fd = open(path, O_RDONLY);
	struct stat	st;
	char		*buffer = NULL;
	ParserResult	result;

	if (fd < 0)
		return (ERROR_RESULT(strerror(errno)));
	if (stat(path, &st) == -1)
		return (ERROR_RESULT(strerror(errno)));
	buffer = malloc(st.st_size + 1);
	if (!buffer)
		return (ERROR_RESULT("Alloc error"));
	buffer[read(fd, buffer, st.st_size)] = 0;
	result = Parser_parseString(buffer, infos);
	free(buffer);
	close(fd);
	return (result);
}