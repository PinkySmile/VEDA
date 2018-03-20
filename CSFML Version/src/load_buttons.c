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
	int 	len = 0;

	if (getLanguage(game->languages, game->settings.lang_id) < 0 || game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons == NULL)
		return ("");
	for (; game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[len]; len++);
	if (nameId < len && game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[nameId])
		return (game->languages[getLanguage(game->languages, game->settings.lang_id)].buttons[nameId]);
	return ("");
}

void	text(char *str, game_t *game, int x, int y)
{
	sfVector2f pos = {x, y};

	if (game->text && sfText_getFont(game->text)) {
		sfText_setString(game->text, str);
		sfText_setPosition(game->text, pos);
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

	if (game->text) {
		sfText_setCharacterSize(game->text, 20);
		sfText_setScale(game->text, game->baseScale);
	}
	for (int i = 0; buttons && buttons[i].content; i++) {
		if (buttons[i].displayed && buttons[i].rect) {
			color = buttons[i].color;
			if (color.g > 200)
				color.g -= 200;
			else
				color.g = 0;
			if (color.b > 200)
				color.b -= 200;
			else
				color.b = 0;
			if (color.r > 200)
				color.r -= 200;
			else
				color.r = 0;
			size = buttons[i].size;
			pos = buttons[i].pos;
			for (int j = 0; j < 10; j++) {
				pos.x += 2;
				pos.y += 2;
				size.x -= 4;
				size.y -= 4;
				sfRectangleShape_setFillColor(buttons[i].rect, color);
				sfRectangleShape_setPosition(buttons[i].rect, pos);
				sfRectangleShape_setSize(buttons[i].rect, size);
				sfRenderWindow_drawRectangleShape(window, buttons[i].rect, NULL);
				if (color.r <= 235 && color.r < buttons[i].color.r - 20)
					color.r += 20;
				else if (color.r < buttons[i].color.r - 20)
					color.r = 255;
				if (color.b <= 235 && color.b < buttons[i].color.b - 20)
					color.b += 20;
				else if (color.b < buttons[i].color.b - 20)
					color.b = 255;
				if (color.g <= 235 && color.g < buttons[i].color.g - 20)
					color.g += 20;
				else if (color.g < buttons[i].color.g - 20)
					color.g = 255;
			}
			text(buttons[i].content, game, buttons[i].pos.x + 20, buttons[i].pos.y + 20);
		}
	}
}

Button	create_button(Button_config config, game_t *game)
{
	Button	button;

	button.content = getButtonContent(config.nameId, game);
	button.pos = (sfVector2f){config.pos.x * game->baseScale.x, config.pos.y * game->baseScale.y};
	button.size = (sfVector2f){config.size.x * game->baseScale.x, config.size.y * game->baseScale.y};
	button.callback = config.callback;
	button.rect = sfRectangleShape_create();
	button.displayed = config.disabled;
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

	for (; button_config[len].nameId >= 0; len++);
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
