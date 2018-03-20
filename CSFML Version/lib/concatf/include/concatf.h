/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** header for my lib
*/

#ifndef __MY_H_
#define __MY_H_ 1

#include <stdbool.h>
#include <stdarg.h>

char	*concatf(char *str, ...);
int	get_nbrlen(int nbr);
char	*concat(char *str1, char *str2, bool free1, bool free2);
char	*my_put_str(char *str);
char	*my_show_str(char *str);
char	*showstr(char const *str);
char    *uint_to_str(unsigned int nb);
char    *int_to_str(int nb);
char	*sub_strings(char const *str, int start, int end, char *buffer);
char	*my_putstarfloat(double *nbr, int format, int format_size);
char	*my_putstarint(int *nbr, int format, int format_size);
char	*my_putstarchar(char *c);
char	*my_putpointer(void *ptr, int format, int format_size);
char	*my_putnbr_unsigned(unsigned int *nbr, int format, int format_size);
char	*my_puthexa(int *nbr);
char	*my_puthexa_cap(int *nbr);
char	*my_putoctal(int *nbr);
char	*my_putbinary(int *nbr);
int	my_compute_power_rec_long(int, int);
char	*my_putnbrbase(unsigned int, char const *);
char	*float_to_str(double nbr, int decimals);

typedef struct {
	char	flag;
	int	type;
	char	*(*fct)(void *);
} flags;

#endif
