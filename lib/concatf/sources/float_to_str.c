/*
** EPITECH PROJECT, 2017
** my_putfloat
** File description:
** Displays a float with a given decimals number
*/

#include "concatf.h"
#include <stdlib.h>

char	*dec_part(int dec_part, int decimals)
{
	char	*result = malloc(decimals);
	int     dec_length = 0;
	int	decimal;

	if (!result)
		return (NULL);
	if (dec_part < 0)
		dec_part *= -1;
	decimal = dec_part;
	do {
		decimal /= 10;
		dec_length++;
	} while (decimal > 0);
	for (int i = decimals - dec_length; i > 0; i--)
		result[decimals - dec_length - i] = '0';
	result[decimals - dec_length] = 0;
	result = concat(result, int_to_str(dec_part), true, true);
	return (result);
}

char	*float_to_str(double nbr, int decimals)
{
	char	*result = NULL;
	long	number;
	long 	exponant;
	int	neg = 1;

	if (nbr < 0)
		neg *= -1;
	exponant = my_compute_power_rec_long(10, decimals);
	number = (long)(exponant * nbr + 0.5 * neg);
	result = concat(int_to_str((int)(number / exponant)), ".", true, false);
	result = concat(result, dec_part(number % exponant, decimals), true, true);
	return (result);
}
