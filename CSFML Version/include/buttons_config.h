#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "structs.h"
#include "functions.h"

const Button_config	button_config[] = {
	{
	        0,
		{640, 100},
		{225, 90},
		{255, 0, 0, 255},
		&play_button,
		true
	},
	{
		-1,
		{0, 0},
		{0, 0},
		{0, 0, 0, 0},
		0,
		false
	}
};
