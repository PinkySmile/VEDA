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
	return (showstr(str));
}

char	*my_put_str(char *str)
{
	return (strdup(str));
}