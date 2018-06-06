#include "configParser.h"
#include <malloc.h>
#include <string.h>

ParserList	*ParserList_getElement(ParserList *list, int index)
{
	int		len = 0;

	for (ParserList *buf; buf->next; buf = buf->next, len++);
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	return (list);
}

bool	ParserList_addElement(ParserList *list, void *data, ParserTypes type, int index)
{
	ParserList	*buffer;
	int		len = 0;

	for (ParserList *buf; buf->next; buf = buf->next, len++);
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	buffer = list->next;
	list->next = malloc(sizeof(*list->next));
	if (!list->next)
		return (false);
	list->next->data = data;
	list->next->type = type;
	list->next->prev = list;
	list->next->next = buffer;
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
		Parser_destroyData(list->data, list->type);
		free(list->prev);
	}
	Parser_destroyData(list->data, list->type);
	free(list->prev);
	free(list);
}