/*
** EPITECH PROJECT, 2017
** my_putbase
** File description:
** All function which displays in a specific base
*/

#include "concatf.h"

char	*my_puthexa(int *nbr)
{
	return (my_putnbrbase(*nbr, "0123456789abcdef"));
}

char	*my_puthexa_cap(int *nbr)
{
	return (my_putnbrbase(*nbr, "0123456789ABCDEF"));
}

char	*my_putoctal(int *nbr)
{
	return (my_putnbrbase(*nbr, "01234567"));
}

char	*my_putbinary(int *nbr)
{
	return (my_putnbrbase(*nbr, "01"));
}
