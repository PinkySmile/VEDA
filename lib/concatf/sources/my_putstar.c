/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** displays
*/

#include "concatf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char	*my_putstarfloat(double *nbr, int format, int format_size)
{
	return (float_to_str(*nbr, 2));
}

char	*my_putstarint(int *nbr, int format, int format_size)
{
	return (int_to_str(*nbr));
}

char	*my_putstarchar(char *c)
{
	char	*result = malloc(2);
	
	result[0] = *c;
	result[1] = 0;
	return (result);
}

char	*my_putpointer(void *ptr, int format, int format_size)
{
	return(ptr ? concat("0x", my_putnbrbase((long)ptr, "0123456789abcdef"), false, true) : strdup("(nil)"));
}

char	*my_putnbr_unsigned(unsigned int *nbr, int format, int format_size)
{
	return (uint_to_str(*nbr));
}
