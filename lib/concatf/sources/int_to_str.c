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

int del_neg(char *str, int nb, int *pos)
{
	if (nb < 0) {
		str[*pos] = '-';
		(*pos)++;
		nb = -nb;
	}
	return (nb);
}

char    *int_to_str(int nb)
{
	int	current_digit;
	int	digit_pos;
	float	number_left;
	int	pos = 0;
	char	*str = malloc(12);

	if (str == NULL)
		return (NULL);
	nb = del_neg(str, nb, &pos);
	number_left = nb;
	current_digit = get_nbrlen(nb);
	digit_pos = current_digit - 1;
	while (digit_pos >= 0) {
		current_digit = number_left / pow(10, digit_pos);
		str[pos] = current_digit + '0';
		pos++;
		number_left -= current_digit * pow(10, digit_pos);
		digit_pos--;
	}
	str[pos] = 0;
	return (str);
}