/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** display a string
*/

#include <string.h>
#include <unistd.h>
#include "concatf.h"

int	my_putstr_stderr(char const *str)
{
	return (write(2, str, strlen(str)));
}
