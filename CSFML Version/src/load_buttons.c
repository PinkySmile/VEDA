#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "buttons_config.h"
#include "structs.h"
#include "macros.h"

void	disableButtons(game_t *game)
{
	for (int i = 0; game->buttons[i].content; i++)
		game->buttons[i].displayed = false;
}

char	*getButtonContent(int nameId, game_t *game)
{
	if (nameId < game->settings.language.buttons.length && ((char **)game->settings.language.buttons.content)[nameId])
		return (((char **)game->settings.language.buttons.content)[nameId]);
	return ("");
}

void	text(char *str, game_t *game, int x, int y)
{
	sfVector2f pos = {x, y};

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
			text(buttons[i].content, game, buttons[i].pos.x + 20, buttons[i].pos.y + 20);
		}
	}
}

Button	create_button(Button_config config, game_t *game)
{
	Button	button;

	button.content = getButtonContent(config.nameId, game);
	button.pos = config.pos;
	button.size = config.size;
	button.callback = config.callback;
	button.rect = sfRectangleShape_create();
	button.displayed = config.disabled;
	if (button.rect) {
		sfRectangleShape_setSize(button.rect, button.size);
		sfRectangleShape_setPosition(button.rect, button.pos);
		sfRectangleShape_setFillColor(button.rect, config.color);
	}
	return (button);
}

Button	*loadButtons(game_t *game)
{
	Button	*buttons = NULL;
	int	len = 0;

	for (; button_config[len].nameId >= 0; len++);
	printf("%s: Loading %i buttons\n", INFO, len);
	buttons = malloc(sizeof(*buttons) * (len + 1));
	if (!buttons) {
		printf("%s: Couldn't malloc %liB for buttons\n", FATAL, sizeof(*buttons) * (len + 1));
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < len; i++)
		buttons[i] = create_button(button_config[i], game);
	buttons[len].content = NULL;
	printf("%s: Buttons loaded !\n", INFO);
	return (buttons);
}
