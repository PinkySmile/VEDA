#include "configParser.h"
#include <malloc.h>
#include <string.h>

ParserList	*ParserList_getElement(ParserList *list, int index)
{
	int		len = 0;

	for (ParserList *buf = list; buf; buf = buf->next, len++);
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	return (list);
}

ParserArray	ParserList_toArray(ParserList *list)
{
	ParserArray	result = {NULL, 0, ParserBooleanType, list};
	int		len = 0;
	int		index = 0;

	result.type = list->type;
	if (!list->data)
		return (result);
	for (ParserList *l = list; l; l = l->next, len++)
		if (result.type != l->type)
			return ((ParserArray){NULL, -1, ParserBooleanType, NULL});
	result.content = malloc(len * getSizeOf(result.type));
	if (!result.content)
		return ((ParserArray){NULL, -1, ParserBooleanType, NULL});
	result.length = len;
	memset(result.content, 0, len * getSizeOf(result.type));
	for (ParserList *l = list; l; l = l->next, index += getSizeOf(result.type))
		for (int i = 0; i < getSizeOf(result.type) && l->data; i++)
			((char *)result.content)[i + index] = ((char *)l->data)[i];
	return (result);
}

bool	ParserList_addElement(ParserList *list, void *data, ParserTypes type, int index)
{
	ParserList	*buffer = NULL;
	ParserString	buff;
	int		len = 0;

	for (ParserList *buf = list; buf; buf = buf->next, len++);
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	if (list->data) {
		buffer = list->next;
		list->next = malloc(sizeof(*list->next));
		if (!list->next)
			return (false);
		list->next->prev = list;
		list = list->next;
		list->next = buffer;
	}
	if (type == ParserStringType) {
		buff.length = strlen(data);
		buff.content = strdup(data);
		list->data = copyData(&buff, type);
	} else
		list->data = copyData(data, type);
	list->type = type;
	return (true);
}

void	destroyListEntry(ParserList *list)
{
	ParserList	buff;

	memset(&buff, 0, sizeof(buff));
	Parser_destroyData(list->data, list->type);
	if (!list->prev) {
		if (list->next) {
			buff = *list->next;
			buff.prev = NULL;
		}
		free(list->next);
		*list = buff;
		return;
	}
	list->prev->next = list->next;
	if (list->next)
		list->next->prev = list->prev;
	free(list);
}

void	ParserList_delElement(ParserList *list, int index)
{
	for (int i = 0; list; list = list->next)
		if (i++ == index) {
			destroyListEntry(list);
			return;
		}
}

void	ParserList_destroy(ParserList *list)
{
	for (; list->next; list = list->next) {
		if (list->prev)
			free(list->prev);
		Parser_destroyData(list->data, list->type);
	}
	if (list->prev)
		free(list->prev);
	Parser_destroyData(list->data, list->type);
	free(list);
}
