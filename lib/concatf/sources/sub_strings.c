/*
** EPITECH PROJECT, 2018
** sub_strings
** File description:
** sub_strings
*/

#include <stdlib.h>

char	*sub_strings(char const *str, int start, int end, char *to_return)
{
	if (!to_return)
		to_return = malloc(end - start + 2);
	if (!to_return)
		return (0);
	for (int i = start; i <= end; i++)
		to_return[i - start] = str[i];
	to_return[end - start + 1] = 0;
	return (to_return);
}
