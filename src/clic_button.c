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

void	which_button(sfVector2f pos, game_t *game)
{
	for (int i = 0; game->buttons[i].content; i++)
		if (button_is_clicked(game->buttons[i], pos, game)) {
			printf("%s: Clicked on button %i (%s)\n", INFO, i, game->buttons[i].content);
			game->buttons[i].callback(game, i);
			break;
		}
}

void	manage_mouse_click(game_t *game, sfMouseButtonEvent event)
{
	sfVector2f	pos = {event.x, event.y};

	if (game->menu == 3) {
		if (pos.x >= 140 * game->baseScale.x && pos.x <= 440 * game->baseScale.x && pos.y >= 4 * game->baseScale.y && pos.y <= 44 * game->baseScale.y) {
			game->selected = 1;
			printf("%s: Clicked on sfx volume control\n", INFO);
		} else if (pos.x >= 140 * game->baseScale.x && pos.x <= 440 * game->baseScale.x && pos.y >= 52 * game->baseScale.y && pos.y <= 92 * game->baseScale.y) {
			game->selected = 2;
			printf("%s: Clicked on music volume control\n", INFO);
		}
	}
	if (event.button == sfMouseLeft)
		which_button(pos, game);
}