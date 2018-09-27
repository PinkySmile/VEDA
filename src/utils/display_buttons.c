#include <SFML/Graphics.h>
#include "structs.h"
#include "utils.h"
#include "concatf.h"
#include "graphic.h"

char	*getButtonContent(int nameId)
{
	int 	len = 0;

	if (nameId < 0)
		return ("");
	if (
		getLanguage(game.ressources.languages, game.settings.lang_id) < 0 ||
		game.ressources.languages[
			getLanguage(game.ressources.languages, game.settings.lang_id)
		].buttons == NULL
	)
		return ("");
	for (
		;
		game.ressources.languages[
			getLanguage(game.ressources.languages, game.settings.lang_id)
		].buttons[len];
		len++
	);
	if (
		nameId < len &&
		game.ressources.languages[
			getLanguage(game.ressources.languages, game.settings.lang_id)
		].buttons[nameId]
	)
		return (
			game.ressources.languages[
				getLanguage(game.ressources.languages, game.settings.lang_id)
			].buttons[nameId]
		);
	return ("");
}

void	dispButtons()
{
	Button		*buttons = game.ressources.buttons;
	sfRenderWindow	*window = game.ressources.window;
	sfVector2f	pos;
	sfVector2f	size;
	sfColor		color;
	int		red;
	int		blue;
	int		green;

	sfText_setCharacterSize(game.ressources.text, 20);
	sfText_setScale(game.ressources.text, game.settings.baseScale);
	for (int i = 0; buttons && buttons[i].content; i++) {
		if (buttons[i].displayed && buttons[i].rect) {
			color.a = buttons[i].color.a;
			red = buttons[i].color.r - 150;
			blue = buttons[i].color.b - 150;
			green = buttons[i].color.g - 150;
			size = buttons[i].size;
			pos = buttons[i].pos;
			for (int j = 0; j < 10; j++) {
				sfVector2f	realSize = {size.x * game.settings.baseScale.x, size.y * game.settings.baseScale.y};
				sfVector2f	realPos = {pos.x * game.settings.baseScale.x, pos.y * game.settings.baseScale.y};

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
			sfText_setColor(game.ressources.text, buttons[i].textColor);
			text(buttons[i].content, buttons[i].pos.x + 10, buttons[i].pos.y + 8, false);
		}
	}
}