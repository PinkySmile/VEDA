/*
** EPITECH PROJECT, 2018
** clic_button.c
** File description:
** Function clic_button which check if the button is clicked.
*/

#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include "structs.h"
#include "my_bool.h"

bool button_is_clicked(button_t button, sfVector2f click_pos)
{
	sfVector2f	size = button.size;
	sfVector2f	pos = button.pos;
	bool	is_in_y = click_pos.x < pos.x + size.x && click_pos.x > pos.x;
	bool	is_in_x = click_pos.y < pos.y + size.y && click_pos.y > pos.y;

	return (is_in_y && is_in_x && button.displayed);
}

void which_button(sfVector2f pos, button_t *buttons, game_t *game)
{
	for (int i = 0; buttons[i].content; i++)
		if (button_is_clicked(buttons[i], pos))
			buttons[i].callback(game);

}

void manage_mouse_click(game_t *game)
{
	button_t *buttons = game->buttons;
	sfVector2i position;
	sfVector2f pos;

	if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue)
		position = sfMouse_getPosition((const sfWindow *)game->window);
	pos.x = position.x;
	pos.y = position.y;
	which_button(pos, buttons, game);
}
