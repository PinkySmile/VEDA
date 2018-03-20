/*
** EPITECH PROJECT, 2017
** concatf
** File description:
** Like printf but concats instead of printing
*/

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "concatf.h"
#include "flags.h"

char	*concat_arg(void ***args, int i, int *index)
{
	char		*result;

	switch (all_flags[i].type) {
	case 0:
		result = all_flags[i].fct((int *)(*args)[*index]);
		free((*args)[*index]);
		(*index)++;
		return (result);
	case 1:
		result = all_flags[i].fct((double *)(*args)[*index]);
		free((*args)[*index]);
		(*index)++;
		return (result);
	case 2:
		result = all_flags[i].fct(*(char **)(*args)[*index]);
		free((*args)[*index]);
		(*index)++;
		return (result);
	default:
		result = all_flags[i].fct(&all_flags[i].type);
		return (result);
	}
}

char	*find_flag(char *str, void ***args, int *index)
{
	char	*temp = NULL;

	for (int i = 0; all_flags[i].flag != 0; i++) {
		if (all_flags[i].flag == *str)
			return (concat_arg(args, i, index));
	}
	temp = malloc(3);
	if (!temp)
		return (NULL);
	temp[0] = '%';
	temp[1] = *str;
	temp[2] = 0;
	return (temp);
}

char	*concatf(char *str, ...)
{
	va_list	args_list;
	char	*result = strdup("");
	void	**args = NULL;
	double	nbrd;
	int	nbri;
	int	start = 0;
	int	size = 0;
	int	nbr = 0;
	int	index = 0;

	va_start(args_list, str);
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == '%') {
			i++;
			for (int j = 0; all_flags[j].flag != 0; j++) {
				if (all_flags[j].flag == str[i]) {
					if (all_flags[j].type >= 0 && all_flags[j].type <= 3) {
						size++;
						args = realloc(args, size * sizeof(*args));
						switch (all_flags[j].type) {
						case 0:
							args[size - 1] = malloc(sizeof(int));
							*(int *)args[size - 1] = va_arg(args_list, int);
							break;
						case 1:
							args[size - 1] = malloc(sizeof(double));
							*(double *)args[size - 1] = va_arg(args_list, double);
							break;
						case 2:
							args[size - 1] = malloc(sizeof(char *));
							*(char **)args[size - 1] = va_arg(args_list, char *);
							break;
						}
					}
				}
			}
		}
	}
	va_end(args_list);
	for (int i = 0; str[i] != 0; i++)
		if (str[i] == '%') {
			result = concat(result, sub_strings(str, start, i - 1, NULL), true, true);
			i++;
			result = concat(result, find_flag(&str[i], &args, &index), true, true);
			start = i + 1;
		}
	result = concat(result, sub_strings(str, start, strlen(str), NULL), true, true);
	free(args);
	return (result);
}
