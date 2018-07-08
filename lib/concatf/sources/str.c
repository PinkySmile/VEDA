/*
** EPITECH PROJECT, 2017
** str
** File description:
** All function which displays strings
*/

#include "concatf.h"
#include <string.h>

char	*my_show_str(char *str)
{
	return (str ? showstr(str) : strdup("(null)"));
}

char	*my_put_str(char *str)
{
	return (str ? strdup(str) : strdup("(null)"));
}