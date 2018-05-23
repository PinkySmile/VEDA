/*
** EPITECH PROJECT, 2017
** flags
** File description:
** all flags for my_printf
*/

#ifndef __FLAGS_H_
#define __FLAGS_H_

#include "concatf.h"
#define ALTERNATE_FORM	1
#define PAD_WITH_ZERO	2
#define PAD_LEFT	3
#define PAD_WITH_SPACES	4
#define	SHOW_SIGN	5

flags   all_flags[] = {
{'f', 1, (void *)&my_putstarfloat},		\
{'d', 0, (void *)&my_putstarint},		\
{'i', 0, (void *)&my_putstarint},		\
{'u', 0, (void *)&my_putnbr_unsigned},		\
{'c', 0, (void *)&my_putstarchar},		\
{'s', 2, (void *)&my_put_str},			\
{'o', 0, (void *)&my_putoctal},			\
{'%', '%', (void *)&my_putstarchar},		\
{'S', 2, (void *)&my_show_str},			\
{'b', 0, (void *)&my_putbinary},		\
{'p', 2, (void *)&my_putpointer},		\
{'x', 0, (void *)&my_puthexa},			\
{'X', 0, (void *)&my_puthexa_cap},		\
{0, 0, 0}					\
};

flags	format_flag[] = {
{'#', ALTERNATE_FORM, 0},	\
{'0', PAD_WITH_ZERO, 0},	\
{'-', PAD_LEFT, 0},		\
{' ', PAD_WITH_SPACES, 0},	\
{'+', SHOW_SIGN, 0},		\
{0, 0, 0}
};

#endif
