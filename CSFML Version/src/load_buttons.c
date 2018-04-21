#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buttons_config.h"
#include "structs.h"
#include "macros.h"
#include "functions.h"

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
		sfText_setColor(game->text, (sfColor){0, 0, 0, 255});
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

Button	create_button(Button_config config, game_t *game, bool createName)
{
	Button	button;

	if (createName)
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

char	*getKeyString(int keyID)
{
	switch (keyID) {
	case (int)sfKeyUnknown:
		return ("Unknown key");
	case (int)sfKeyA:
		return ("A");
	case (int)sfKeyB:
		return ("B");
	case (int)sfKeyC:
		return ("C");
	case (int)sfKeyD:
		return ("D");
	case (int)sfKeyE:
		return ("E");
	case (int)sfKeyF:
		return ("F");
	case (int)sfKeyG:
		return ("G");
	case (int)sfKeyH:
		return ("H");
	case (int)sfKeyI:
		return ("I");
	case (int)sfKeyJ:
		return ("J");
	case (int)sfKeyK:
		return ("K");
	case (int)sfKeyL:
		return ("L");
	case (int)sfKeyM:
		return ("M");
	case (int)sfKeyN:
		return ("N");
	case (int)sfKeyO:
		return ("O");
	case (int)sfKeyP:
		return ("P");
	case (int)sfKeyQ:
		return ("Q");
	case (int)sfKeyR:
		return ("R");
	case (int)sfKeyS:
		return ("S");
	case (int)sfKeyT:
		return ("T");
	case (int)sfKeyU:
		return ("U");
	case (int)sfKeyV:
		return ("V");
	case (int)sfKeyW:
		return ("W");
	case (int)sfKeyX:
		return ("X");
	case (int)sfKeyY:
		return ("Y");
	case (int)sfKeyZ:
		return ("Z");
	case (int)sfKeyNum0:
		return ("0");
	case (int)sfKeyNum1:
		return ("1");
	case (int)sfKeyNum2:
		return ("2");
	case (int)sfKeyNum3:
		return ("3");
	case (int)sfKeyNum4:
		return ("4");
	case (int)sfKeyNum5:
		return ("5");
	case (int)sfKeyNum6:
		return ("6");
	case (int)sfKeyNum7:
		return ("7");
	case (int)sfKeyNum8:
		return ("8");
	case (int)sfKeyNum9:
		return ("9");
	case (int)sfKeyEscape:
		return ("Esc");
	case (int)sfKeyLControl:
		return ("Left CTRL");
	case (int)sfKeyRControl:
		return ("Right CTRL");
	case (int)sfKeyLShift:
		return ("Left Shift");
	case (int)sfKeyRShift:
		return ("Right Shift");
	case (int)sfKeyLAlt:
		return ("Left Alt");
	case (int)sfKeyRAlt:
		return ("Right Alt");
	case (int)sfKeyLSystem:
		return ("Left OS Key");
	case (int)sfKeyRSystem:
		return ("Right OS Key");
	case (int)sfKeyMenu:
		return ("Menu");
	case (int)sfKeyLBracket:
		return ("[");
	case (int)sfKeyRBracket:
		return ("]");
	case (int)sfKeySemiColon:
		return (";");
	case (int)sfKeyComma:
		return (",");
	case (int)sfKeyPeriod:
		return (".");
	case (int)sfKeyQuote:
		return ("'");
	case (int)sfKeySlash:
		return ("/");
	case (int)sfKeyBackSlash:
		return ("\\");
	case (int)sfKeyTilde:
		return ("~");
	case (int)sfKeyEqual:
		return ("=");
	case (int)sfKeyDash:
		return ("-");
	case (int)sfKeySpace:
		return ("Space");
	case (int)sfKeyReturn:
		return ("Return");
	case (int)sfKeyBack:
		return ("Backspace");
	case (int)sfKeyTab:
		return ("Tab");
	case (int)sfKeyPageUp:
		return ("Page Up");
	case (int)sfKeyPageDown:
		return ("Page Down");
	case (int)sfKeyEnd:
		return ("End");
	case (int)sfKeyHome:
		return ("Home");
	case (int)sfKeyInsert:
		return ("Insert");
	case (int)sfKeyDelete:
		return ("Del");
	case (int)sfKeyAdd:
		return ("+");
	case (int)sfKeySubtract:
		return ("Minus");
	case (int)sfKeyMultiply:
		return ("*");
	case (int)sfKeyDivide:
		return ("Divide");
	case (int)sfKeyLeft:
		return ("Left Arrow");
	case (int)sfKeyRight:
		return ("Right Arrow");
	case (int)sfKeyUp:
		return ("Up Arrow");
	case (int)sfKeyDown:
		return ("Down Arrow");
	case (int)sfKeyNumpad0:
		return ("Pad 0");
	case (int)sfKeyNumpad1:
		return ("Pad 1");
	case (int)sfKeyNumpad2:
		return ("Pad 2");
	case (int)sfKeyNumpad3:
		return ("Pad 3");
	case (int)sfKeyNumpad4:
		return ("Pad 4");
	case (int)sfKeyNumpad5:
		return ("Pad 5");
	case (int)sfKeyNumpad6:
		return ("Pad 6");
	case (int)sfKeyNumpad7:
		return ("Pad 7");
	case (int)sfKeyNumpad8:
		return ("Pad 8");
	case (int)sfKeyNumpad9:
		return ("Pad 9");
	case (int)sfKeyF1:
		return ("F1");
	case (int)sfKeyF2:
		return ("F2");
	case (int)sfKeyF3:
		return ("F3");
	case (int)sfKeyF4:
		return ("F4");
	case (int)sfKeyF5:
		return ("F5");
	case (int)sfKeyF6:
		return ("F6");
	case (int)sfKeyF7:
		return ("F7");
	case (int)sfKeyF8:
		return ("F8");
	case (int)sfKeyF9:
		return ("F9");
	case (int)sfKeyF10:
		return ("F10");
	case (int)sfKeyF11:
		return ("F11");
	case (int)sfKeyF12:
		return ("F12");
	case (int)sfKeyF13:
		return ("F13");
	case (int)sfKeyF14:
		return ("F14");
	case (int)sfKeyF15:
		return ("F15");
	case (int)sfKeyPause:
		return ("Pause");
	default:
		return ("Unknown key");
	}
}

Button	*loadButtons(game_t *game)
{
	Button		*buttons = NULL;
	int		len = 0;
	int		langs = 0;
	Button_config	config;

	for (; button_config[len].callback; len++);
	for (; game->languages && game->languages[langs].name; langs++);
	printf("%s: Loading %i buttons\n", INFO, len + langs + NB_OF_KEYS);
	buttons = malloc(sizeof(*buttons) * (len + langs + NB_OF_KEYS + 1));
	if (!buttons) {
		printf("%s: Couldn't malloc %liB for buttons\n", FATAL, sizeof(*buttons) * (len + langs + NB_OF_KEYS + 1));
		exit(EXIT_FAILURE);
	}
	game->languagesConf.y = langs;
	game->languagesConf.x = len;
	memset(buttons, 0, sizeof(*buttons) * (len + langs + 1));
	for (int i = 0; button_config[i].callback; i++) {
		displayLoadingBar(game, 6, MAX_STEPS, i, len + langs + NB_OF_KEYS, "Creating buttons");
		buttons[i] = create_button(button_config[i], game, true);
	}
	for (int i = 0; game->languages && game->languages[i].name; i++) {
		displayLoadingBar(game, 6, MAX_STEPS, i + len, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){300 - strlen(game->languages[i].name) * 7, 50 * i + 10};
		config.size = (sfVector2f){40 + strlen(game->languages[i].name) * 7, 40};
		config.color = (sfColor){255, 255, 0, 255};
		config.callback = &changeLanguage;
		config.disabled = false;
		buttons[i + len] = create_button(config, game, false);
		buttons[i + len].content = game->languages[i].name;
	}
	for (int i = 0; i < NB_OF_KEYS; i++) {
		displayLoadingBar(game, 6, MAX_STEPS, i + len + langs, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){115 + i / 10 * 272, i % 10 * 48 + 5};
		config.size = (sfVector2f){150, 40};
		config.color = (sfColor){255, 255, 255, 255};
		config.callback = &changeKey;
		config.disabled = false;
		buttons[i + len + langs] = create_button(config, game, false);
	}
	buttons[len + langs].content = NULL;
	printf("%s: Buttons loaded !\n", INFO);
	return (buttons);
}
