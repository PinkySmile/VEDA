#ifndef __LIST_HEADER_
#define __LIST_HEADER_

typedef struct list_s list_t;
struct list_s {
	void	*data;
	list_t	*prev;
	list_t	*next;
};

#endif