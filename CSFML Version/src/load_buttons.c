#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "buttons_config.h"
#include "structs.h"
#include "macros.h"

char	*getButtonContent(int nameId, game_t *game)
{
	int 	len = 0;

	if (nameId < 0)
		return ("");
	if (getLanguage(game->languages, game->settings.lang_id) < 0 || game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons == NULL)
		return ("");
	for (; game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[len]; len++);
	if (nameId < len && game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[nameId])
		return (game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[nameId]);
	return ("");
}

void	text(char *str, game_t *game, int x, int y)
{
	sfVector2f pos = {x * game->baseScale.x, y * game->baseScale.y};

	if (game->text && sfText_getFont(game->text)) {
		sfText_setString(game->text, str);
		sfText_setPosition(game->text, pos);
		sfText_setScale(game->text, game->baseScale);
		sfRenderWindow_drawText(game->window, game->text, 0);
	}
}

void	disp_buttons(game_t *game)
{
	Button		*buttons = game->buttons;
	sfRenderWindow	*window = game->window;
	sfVector2f	pos;
	sfVector2f	size;
	sfColor		color;
	int		red;
	int		blue;
	int		green;

	if (game->text) {
		sfText_setCharacterSize(game->text, 20);
		sfText_setScale(game->text, game->baseScale);
	}
	for (int i = 0; buttons && buttons[i].content; i++) {
		if (buttons[i].displayed && buttons[i].rect) {
			color.a = buttons[i].color.a;
			red = buttons[i].color.r - 150;
			blue = buttons[i].color.b - 150;
			green = buttons[i].color.g - 150;
			size = buttons[i].size;
			pos = buttons[i].pos;
			for (int j = 0; j < 10; j++) {
				sfVector2f	realSize = {size.x * game->baseScale.x, size.y * game->baseScale.y};
				sfVector2f	realPos = {pos.x * game->baseScale.x, pos.y * game->baseScale.y};

				pos.x += 1;
				pos.y += 1;
				size.x -= 2;
				size.y -= 2;
				if (red < 0)
					color.r = 0;
				else if (red > 255)
					color.r = 255;
				else
					color.r = red;
				if (green < 0)
					color.g = 0;
				else if (green > 255)
					color.g = 255;
				else
					color.g = green;
				if (blue < 0)
					color.b = 0;
				else if (blue > 255)
					color.b = 255;
				else
					color.b = blue;
				sfRectangleShape_setFillColor(buttons[i].rect, color);
				sfRectangleShape_setPosition(buttons[i].rect, realPos);
				sfRectangleShape_setSize(buttons[i].rect, realSize);
				sfRenderWindow_drawRectangleShape(window, buttons[i].rect, NULL);
			        red += 15;
			        blue += 15;
			        green += 15;
			}
			text(buttons[i].content, game, buttons[i].pos.x + 10, buttons[i].pos.y + 8);
		}
	}
}

Button	create_button(Button_config config, game_t *game)
{
	Button	button;

	button.content = getButtonContent(config.nameId, game);
	button.pos = (sfVector2f){config.pos.x, config.pos.y};
	button.size = (sfVector2f){config.size.x, config.size.y};
	button.callback = config.callback;
	button.rect = sfRectangleShape_create();
	button.displayed = config.disabled;
	button.active = config.disabled;
	button.color = config.color;
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

	for (; button_config[len].callback; len++);
	printf("%s: Loading %i buttons\n", INFO, len);
	buttons = malloc(sizeof(*buttons) * (len + 1));
	if (!buttons) {
		printf("%s: Couldn't malloc %liB for buttons\n", FATAL, sizeof(*buttons) * (len + 1));
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < len; i++) {
		displayLoadingBar(game, 6, MAX_STEPS, i, len, "Creating buttons");
		buttons[i] = create_button(button_config[i], game);
	}
	buttons[len].content = NULL;
	printf("%s: Buttons loaded !\n", INFO);
	return (buttons);
}
