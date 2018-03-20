/*
** EPITECH PROJECT, 2017
** int_to_str
** File description:
** prints a number given as argument
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "concatf.h"

char    *uint_to_str(unsigned int nb)
{
	int		current_digit;
	int		digit_pos;
	unsigned int	number_left;
	int		pos = 0;
	char		*str = malloc(12);

	if (str == NULL)
		return (NULL);
	number_left = nb;
	current_digit = get_nbrlen(nb);
	digit_pos = current_digit - 1;
	while (digit_pos >= 0) {
		current_digit = number_left / pow(10, digit_pos);
		str[pos] = current_digit + 48;
		pos++;
		number_left -= current_digit * pow(10, digit_pos);
		digit_pos--;
	}
	str[pos] = 0;
	return (str);
}
