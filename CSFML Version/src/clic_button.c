#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

bool	button_is_clicked(Button button, sfVector2f click_pos, game_t *game)
{
	sfVector2f	size = {button.size.x * game->baseScale.x, button.size.y * game->baseScale.y};
	sfVector2f	pos = {button.pos.x * game->baseScale.x, button.pos.y * game->baseScale.y};
	bool		is_in_y = click_pos.x < pos.x + size.x && click_pos.x > pos.x;
	bool		is_in_x = click_pos.y < pos.y + size.y && click_pos.y > pos.y;

	return (is_in_y && is_in_x && button.active);
}

void	which_button(sfVector2f pos, Button *buttons, game_t *game)
{
	for (int i = 0; buttons[i].content; i++)
		if (button_is_clicked(buttons[i], pos, game)) {
			printf("%s: Clicked on button %i (%s)\n", INFO, i, buttons[i].content);
			buttons[i].callback(game, i);
		}

}

void	manage_mouse_click(game_t *game)
{
	Button		*buttons = game->buttons;
	sfVector2i	position;
	sfVector2f	pos;

	position = sfMouse_getPosition((const sfWindow *)game->window);
	pos.x = position.x;
	pos.y = position.y;
	printf("%s: Mouse click at position (%i, %i)\n", INFO, position.x, position.y);
	if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue)
		which_button(pos, buttons, game);
}
