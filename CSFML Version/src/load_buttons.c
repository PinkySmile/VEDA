/*
** EPITECH PROJECT, 2018
** load_buttons
** File description:
** Loads all the buttons
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "buttons_config.h"
#include "structs.h"
#include "macros.h"

char	*getButtonContent(int nameId, game_t *game)
{
	if (nameId < game.settings.language.buttons.length && ((char **)game.settings.language.buttons.content)[nameId])
		return (((char **)game.settings.language.buttons.content)[nameId]);
	return ("");
}

void	disp_text(char *str, game_t *game, sfVector2f pos)
{
	pos.x += 20;
	pos.y += 20;
	if (game->text) {
		sfText_setString(game->text, str);
		sfText_setPosition(game->text, pos);
		sfRenderWindow_drawText(game->window, game->text, 0);
	}
}

void	disp_buttons(game_t *game)
{
	Button		*buttons = game->buttons;
	sfRenderWindow	*window = game->window;

	if (game->text)
		sfText_setCharacterSize(game->text, 50);
	for (int i = 0; buttons && buttons[i].content; i++) {
		if (buttons[i].displayed && buttons[i].rect) {
			sfRenderWindow_drawRectangleShape(window, buttons[i].rect, NULL);
			disp_text(buttons[i].content, game, buttons[i].pos);
		}
	}
}

Button	create_button(Button_config config)
{
	Button	button;

	button.content = getButtonContent(config.nameId);
	button.pos = config.pos;
	button.size = config.size;
	button.callback = config.callback;
	button.rect = sfRectangleShape_create();
	button.displayed = 1;
	if (button.rect) {
		sfRectangleShape_setSize(button.rect, button.size);
		sfRectangleShape_setPosition(button.rect, button.pos);
		sfRectangleShape_setFillColor(button.rect, config.color);
	}
	return (button);
}

Button	*load_buttons(void)
{
	Button	*buttons = NULL;
	int	len = 0;

	for (; button_config[len].nameId; len++);
	buttons = malloc(sizeof(*buttons) * (len + 1));
	if (!buttons) {
		printf("%s: Couldn't malloc %liB for buttons\n", FATAL, sizeof(*buttons) * (len + 1));
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < len; i++)
		buttons[i] = create_button(button_config[i]);
	buttons[len].content = NULL;
	return (buttons);
}
