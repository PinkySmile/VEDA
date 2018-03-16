/*
** EPITECH PROJECT, 2018
** button_config
** File description:
** Config file for buttons
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "structs.h"
#include "functions.h"

Button_config const	button_config[] = {
	{
	        1,
		{640, 100},
		{225, 90},
		{255, 0, 0, 255},
		&play_button
	},
	{
		0,
		{0, 0},
		{0, 0},
		{0, 0, 0, 0},
		0
	}
};
