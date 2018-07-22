#include "configParser.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define ERROR_RESULT(message)	((ParserResult){NULL, 0, message})

void	delChar(char *str, int i)
{
	for (int j = i; str[j]; j++)
		str[j] = str[j + 1];
}

bool	startWith(char *str, char *start)
{
	if (!start)
		return (false);
	for (int i = 0; start[i]; i++)
		if (start[i] != str[i])
			return (false);
	return (true);
}

int	isInString(char c, char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] == c)
			return (i);
	return (-1);
}

char	getNumberBase(char *str, char *base)
{
	char	result = 0;

	for (int i = 0; i < (strlen(base) == 16 ? 2 : 3) && isInString(*str, base) > -1; i++) {
		result *= strlen(base);
		result += isInString(*str, base);
		delChar(str, 0);
	}
	return (result);
}

char	*verifString(char *str, ParserInfos *infos)
{
	int	arrLvl = 0;
	int	objLvl = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == infos->objOpen)
			objLvl++;
		if (str[i] == infos->arrOpen)
			arrLvl++;
		if (str[i] == infos->objClose)
			objLvl--;
		if (str[i] == infos->arrClose)
			arrLvl--;
		if (arrLvl < 0)
			return ("Unexpected array closer character");
		if (objLvl < 0)
			return ("Unexpected object closer character");
	}
	return (NULL);
}

void	replaceEscapeSequence(char *str, int index)
{
	switch (str[index]) {
	case 'a':
		str[index] = '\a';
		break;
	case 'b':
		str[index] = '\b';
		break;
	case 't':
		str[index] = '\t';
		break;
	case 'r':
		str[index] = '\r';
		break;
	case 'n':
		str[index] = '\n';
		break;
	case 'v':
		str[index] = '\v';
		break;
	case 'e':
		str[index] = '\x1b';
		break;
	case 'f':
		str[index] = '\f';
		break;
	case 'x':
		if (isdigit(str[index + 1]) || (str[index + 1] >= 'a' && str[index + 1] <= 'f'))
			str[index] = getNumberBase(&str[index + 1], "0123456789abcdef");
		break;
	case '0':
		if (str[index + 1] < '0' || str[index + 1] > '7')
			str[index] = '\0';
		else
			str[index] = getNumberBase(&str[index + 1], "01234567");
		break;
	}
}

char	*cleanString(char *str, ParserInfos *infos)
{
	int	quote = -1;
	int	i = 0;

	while (str[i]) {
		if (quote == -1 && startWith(&str[i], infos->multLineCommentStart)) {
			for (int j = 0; j < (int)strlen(infos->multLineCommentStart); j++)
				delChar(str, i);
			while (!startWith(&str[i], infos->multLineCommentEnd)) {
				if (!str[i]) {
					printf("ParserError: Unfinished comment\n");
					return ("Unfinished comment");
				}
				delChar(str, i);
			}
			for (int j = 0; j < (int)strlen(infos->multLineCommentEnd); j++)
				delChar(str, i);
			continue;
		}
		if (quote == -1 && startWith(&str[i], infos->singLineComment)) {
			for (int j = 0; j < (int)strlen(infos->singLineComment); j++)
				delChar(str, i);
			while (str[i] && str[i] != '\n')
				delChar(str, i);
			continue;
		}
		if (quote == -1 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
			delChar(str, i);
			continue;
		}
		if (quote != -1 && str[i] == infos->strChar[quote])
			quote = -1;
		else if (quote == -1)
			quote = isInString(str[i], infos->strChar);
		if (str[i] == '\\') {
			delChar(str, i);
			replaceEscapeSequence(str, i);
		}
		i++;
	}
	return (NULL);
}

bool	isFloat(char *str, ParserInfos *infos)
{
	int	i = 0;

	for (; str[i] == '-' || str[i] == '+'; i++);
	for (; isdigit(str[i]); i++);
	if (i == 0)
		return (false);
	if (str[i] == '.')
		i++;
	for (; isdigit(str[i]); i++);
	return (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->objClose);
}

bool	isNbr(char *str, ParserInfos *infos)
{
	int	i = 0;

	for (; str[i] == '-' || str[i] == '+'; i++);
	for (; isdigit(str[i]); i++);
	if (i == 0)
		return (false);
	return (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->objClose);
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
	return (found && (str[i] == infos->separator || str[i] == infos->arrClose || str[i] == infos->objClose));
}

ParserResult	getValue(char *str, ParserInfos *infos)
{
	ParserResult	result;
	ParserResult	buff;
	int		index = 0;
	int		index2 = 0;
	ParserObj	*obj;
	ParserList	*list;
	int		arrlvl = 0;
	int		objlvl = 0;

	memset(&result, 0, sizeof(result));
	if (!*str) {
		printf("ParserError: Unexpected <EOF>\n");
		return (ERROR_RESULT("Unexpected <EOF>"));
	}
	if (*str == infos->objOpen && isInString(str[1], infos->strChar) >= 0) {
		index = 1;
		result.type = ParserObjType;
		result.data = malloc(sizeof(ParserObj));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		obj = result.data;
		memset(obj, 0, sizeof(*obj));
		while (str[index] != infos->objClose && str[index]) {
			if (isInString(str[index], infos->strChar) == -1) {
				ParserObj_destroy(result.data);
				return (ERROR_RESULT("Obj keys must be strings"));
			}
			for (index2 = index + 1; infos->strChar[isInString(str[index], infos->strChar)] != str[index2]; index2++) {
				if (!str[index2]) {
					ParserObj_destroy(result.data);
					str[index + (index2 > 10 ? 10 : index2)] = 0;
					printf("ParserError: Unfinished string after '%s'\n", &str[index]);
					return (ERROR_RESULT("Unfinished string found"));
				}
			}
			if (obj->data) {
				obj->next = malloc(sizeof(*obj->next));
				if (!obj->next) {
					ParserObj_destroy(result.data);
					return (ERROR_RESULT("Alloc error"));
				}
				memset(obj->next, 0, sizeof(*obj->next));
				obj->next->prev = obj;
				obj = obj->next;
			}
			obj->index = malloc(index2 - index);
			if (!obj->index) {
				ParserObj_destroy(result.data);
				return (ERROR_RESULT("Alloc error"));
			}
			memset(obj->index, 0, index2 - index - 1);
			strncpy(obj->index, &str[index + 1], index2 - index - 1);
			obj->index[index2 - index - 1] = 0;
			index = index2 + 1;
			if (str[index] != infos->eqChar) {
				printf("ParserError: Expected equal character after obj key '%s'\n", obj->index);
				ParserObj_destroy(result.data);
				return (ERROR_RESULT("Expected equal character after obj key"));
			}
			index++;
			buff = getValue(&str[index], infos);
			if (buff.error) {
				ParserObj_destroy(result.data);
				return (buff);
			}
			obj->data = buff.data;
			obj->type = buff.type;
			for (; str[index] && ((str[index] != infos->objClose && str[index] != infos->separator) || arrlvl > 0 || objlvl > 0); index++) {
				if (str[index] == infos->objOpen)
					objlvl++;
				else if (str[index] == infos->arrOpen)
					arrlvl++;
				else if (str[index] == infos->objClose)
					objlvl--;
				else if (str[index] == infos->arrClose)
					arrlvl--;
			}
			if (str[index] == infos->separator)
				index++;
		}
		if (!str[index]) {
			ParserObj_destroy(result.data);
			printf("ParserError: Expected '%c' before <EOF>\n", infos->objClose);
			return (ERROR_RESULT("Unexpected <EOF>"));
		}
		if (str[index + 1] != infos->separator && str[index + 1] != infos->objClose && str[index + 1] != infos->arrClose && str[index + 1]) {
			ParserObj_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after an object\n", str[index + 1]);
			return (ERROR_RESULT("Unexpected character found after an object"));
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
			for (; str[index] && ((str[index] != infos->arrClose && str[index] != infos->separator) || arrlvl > 0 || objlvl > 0); index++) {
				if (str[index] == infos->objOpen)
					objlvl++;
				else if (str[index] == infos->arrOpen)
					arrlvl++;
				else if (str[index] == infos->objClose)
					objlvl--;
				else if (str[index] == infos->arrClose)
					arrlvl--;
			}
			if (str[index] == infos->separator)
				index++;
		}
		if (!str[index]) {
			ParserList_destroy(result.data);
			printf("ParserError: Expected '%c' before <EOF>\n", infos->arrClose);
			return (ERROR_RESULT("Unexpected <EOF>"));
		}
		if (str[index + 1] != infos->separator && str[index + 1] != infos->objClose && str[index + 1] != infos->arrClose && str[index + 1]) {
			ParserList_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after an array\n", str[index + 1]);
			return (ERROR_RESULT("Unexpected character found after an array"));
		}
		if (infos->listToArray) {
			list = result.data;
			result.type = ParserArrayType;
			result.data = malloc(sizeof(ParserArray));
			*(ParserArray *)result.data = ParserList_toArray(list);
			if (((ParserArray *)result.data)->length < 0) {
				free(result.data);
				result.data = list;
				result.type = ParserListType;
			}
		}
	} else if (isNbr(str, infos)) {
		result.type = ParserIntType;
		result.data = malloc(sizeof(ParserInt));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		*(ParserInt *)result.data = atoi(str);
		for (; str[index] == '-' || str[index] == '+'; index++);
		for (; isdigit(str[index]); index++);
		if (str[index] != infos->separator && str[index] != infos->objClose && str[index] != infos->arrClose && str[index]) {
			ParserInt_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after an integer\n", str[index]);
			return (ERROR_RESULT("Unexpected character found after an integer"));
		}
	} else if (isFloat(str, infos)) {
		result.type = ParserFloatType;
		result.data = malloc(sizeof(ParserFloat));
		if (!result.data)
			return (ERROR_RESULT("Alloc error"));
		*(ParserFloat *)result.data = atof(str);
		for (; str[index] == '-' || str[index] == '+'; index++);
		for (; isdigit(str[index]); index++);
		if (str[index] == '.')
			index++;
		for (; isdigit(str[index]); index++);
		if (str[index] != infos->separator && str[index] != infos->objClose && str[index] != infos->arrClose && str[index]) {
			ParserFloat_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after a float\n", str[index]);
			return (ERROR_RESULT("Unexpected character found after a float"));
		}
	} else if (isInString(*str, infos->strChar) >= 0) {
		result.type = ParserStringType;
		for (index = 1; infos->strChar[isInString(str[0], infos->strChar)] != str[index]; index++)
			if (!str[index]) {
				str[index > 10 ? 10 : index] = 0;
				printf("ParserError: Unfinished string after '%s'\n", str);
				return (ERROR_RESULT("Unfinished string found"));
			}
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
		if (str[index + 1] != infos->separator && str[index + 1] != infos->objClose && str[index + 1] != infos->arrClose && str[index + 1]) {
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
		if (str[index + (*str == 't' ? 4 : 5)] != infos->separator && str[index + (*str == 't' ? 4 : 5)] != infos->objClose && str[index + (*str == 't' ? 4 : 5)] != infos->arrClose && str[index + (*str == 't' ? 4 : 5)]) {
			ParserBoolean_destroy(result.data);
			printf("ParserError: Unexpected '%c' found after a boolean\n", str[index + (*str == 't' ? 4 : 5)]);
			return (ERROR_RESULT("Unexpected character found after a boolean"));
		}
	} else {
		printf("ParserError: Unexpected character '%c'\n", *str);
		return (ERROR_RESULT("Unexpected character found"));
	}
	return (result);
}

ParserResult	Parser_parseString(char *string, ParserInfos *infos)
{
	ParserResult	result;

	memset(&result, 0, sizeof(result));
	string = strdup(string);
	if (!infos)
		infos = JSON_COMPACT;
	if (!string)
		return (ERROR_RESULT("Couldn't copy string"));
	result.error = cleanString(string, infos);
	if (result.error) {
		free(string);
		return (result);
	}
	result.error = verifString(string, infos);
	if (result.error) {
		free(string);
		return (result);
	}
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

	if (fd < 0) {
		printf("ParserError: %s: %s\n", path, strerror(errno));
		return (ERROR_RESULT(strerror(errno)));
	}
	if (stat(path, &st) == -1) {
		printf("ParserError: %s: %s\n", path, strerror(errno));
		return (ERROR_RESULT(strerror(errno)));
	}
	buffer = malloc(st.st_size + 1);
	if (!buffer)
		return (ERROR_RESULT("Alloc error"));
	buffer[read(fd, buffer, st.st_size)] = 0;
	result = Parser_parseString(buffer, infos);
	free(buffer);
	close(fd);
	return (result);
}
