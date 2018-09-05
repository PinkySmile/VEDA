#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buttons_config.h"
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "concatf.h"

char	*getButtonContent(int nameId)
{
	int 	len = 0;

	if (nameId < 0)
		return ("");
	if (getLanguage(game.ressources.languages, game.settings.lang_id) < 0 || game.ressources.languages[getLanguage(game.ressources.languages, game.settings.lang_id)].buttons == NULL)
		return ("");
	for (; game.ressources.languages[getLanguage(game.ressources.languages, game.settings.lang_id)].buttons[len]; len++);
	if (nameId < len && game.ressources.languages[getLanguage(game.ressources.languages, game.settings.lang_id)].buttons[nameId])
		return (game.ressources.languages[getLanguage(game.ressources.languages, game.settings.lang_id)].buttons[nameId]);
	return ("");
}

void	disp_buttons()
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

Button	create_button(Button_config config, bool createName)
{
	Button	button;

	if (createName)
		button.content = getButtonContent(config.nameId);
	button.pos = (sfVector2f){config.pos.x, config.pos.y};
	button.size = (sfVector2f){config.size.x, config.size.y};
	button.callback = config.callback;
	button.rect = sfRectangleShape_create();
	button.displayed = config.disabled;
	button.active = config.disabled;
	button.color = config.color;
	button.textColor = config.textColor;
	if (button.rect) {
		sfRectangleShape_setSize(button.rect, button.size);
		sfRectangleShape_setPosition(button.rect, button.pos);
		sfRectangleShape_setFillColor(button.rect, config.color);
	}
	return (button);
}

char	*getKeyString(unsigned char keyID)
{
	switch (keyID) {
	case (unsigned char)sfKeyUnknown:
		return ("None");
	case (unsigned char)sfKeyA:
		return ("A");
	case (unsigned char)sfKeyB:
		return ("B");
	case (unsigned char)sfKeyC:
		return ("C");
	case (unsigned char)sfKeyD:
		return ("D");
	case (unsigned char)sfKeyE:
		return ("E");
	case (unsigned char)sfKeyF:
		return ("F");
	case (unsigned char)sfKeyG:
		return ("G");
	case (unsigned char)sfKeyH:
		return ("H");
	case (unsigned char)sfKeyI:
		return ("I");
	case (unsigned char)sfKeyJ:
		return ("J");
	case (unsigned char)sfKeyK:
		return ("K");
	case (unsigned char)sfKeyL:
		return ("L");
	case (unsigned char)sfKeyM:
		return ("M");
	case (unsigned char)sfKeyN:
		return ("N");
	case (unsigned char)sfKeyO:
		return ("O");
	case (unsigned char)sfKeyP:
		return ("P");
	case (unsigned char)sfKeyQ:
		return ("Q");
	case (unsigned char)sfKeyR:
		return ("R");
	case (unsigned char)sfKeyS:
		return ("S");
	case (unsigned char)sfKeyT:
		return ("T");
	case (unsigned char)sfKeyU:
		return ("U");
	case (unsigned char)sfKeyV:
		return ("V");
	case (unsigned char)sfKeyW:
		return ("W");
	case (unsigned char)sfKeyX:
		return ("X");
	case (unsigned char)sfKeyY:
		return ("Y");
	case (unsigned char)sfKeyZ:
		return ("Z");
	case (unsigned char)sfKeyNum0:
		return ("0");
	case (unsigned char)sfKeyNum1:
		return ("1");
	case (unsigned char)sfKeyNum2:
		return ("2");
	case (unsigned char)sfKeyNum3:
		return ("3");
	case (unsigned char)sfKeyNum4:
		return ("4");
	case (unsigned char)sfKeyNum5:
		return ("5");
	case (unsigned char)sfKeyNum6:
		return ("6");
	case (unsigned char)sfKeyNum7:
		return ("7");
	case (unsigned char)sfKeyNum8:
		return ("8");
	case (unsigned char)sfKeyNum9:
		return ("9");
	case (unsigned char)sfKeyEscape:
		return ("Esc");
	case (unsigned char)sfKeyLControl:
		return ("Left CTRL");
	case (unsigned char)sfKeyRControl:
		return ("Right CTRL");
	case (unsigned char)sfKeyLShift:
		return ("Left Shift");
	case (unsigned char)sfKeyRShift:
		return ("Right Shift");
	case (unsigned char)sfKeyLAlt:
		return ("Left Alt");
	case (unsigned char)sfKeyRAlt:
		return ("Right Alt");
	case (unsigned char)sfKeyLSystem:
		return ("Left OS Key");
	case (unsigned char)sfKeyRSystem:
		return ("Right OS Key");
	case (unsigned char)sfKeyMenu:
		return ("Menu");
	case (unsigned char)sfKeyLBracket:
		return ("[");
	case (unsigned char)sfKeyRBracket:
		return ("]");
	case (unsigned char)sfKeySemiColon:
		return (";");
	case (unsigned char)sfKeyComma:
		return (",");
	case (unsigned char)sfKeyPeriod:
		return (".");
	case (unsigned char)sfKeyQuote:
		return ("'");
	case (unsigned char)sfKeySlash:
		return ("/");
	case (unsigned char)sfKeyBackSlash:
		return ("\\");
	case (unsigned char)sfKeyTilde:
		return ("~");
	case (unsigned char)sfKeyEqual:
		return ("=");
	case (unsigned char)sfKeyDash:
		return ("-");
	case (unsigned char)sfKeySpace:
		return ("Space");
	case (unsigned char)sfKeyReturn:
		return ("Return");
	case (unsigned char)sfKeyBack:
		return ("Backspace");
	case (unsigned char)sfKeyTab:
		return ("Tab");
	case (unsigned char)sfKeyPageUp:
		return ("Page Up");
	case (unsigned char)sfKeyPageDown:
		return ("Page Down");
	case (unsigned char)sfKeyEnd:
		return ("End");
	case (unsigned char)sfKeyHome:
		return ("Home");
	case (unsigned char)sfKeyInsert:
		return ("Insert");
	case (unsigned char)sfKeyDelete:
		return ("Del");
	case (unsigned char)sfKeyAdd:
		return ("+");
	case (unsigned char)sfKeySubtract:
		return ("Minus");
	case (unsigned char)sfKeyMultiply:
		return ("*");
	case (unsigned char)sfKeyDivide:
		return ("Divide");
	case (unsigned char)sfKeyLeft:
		return ("Left Arrow");
	case (unsigned char)sfKeyRight:
		return ("Right Arrow");
	case (unsigned char)sfKeyUp:
		return ("Up Arrow");
	case (unsigned char)sfKeyDown:
		return ("Down Arrow");
	case (unsigned char)sfKeyNumpad0:
		return ("Pad 0");
	case (unsigned char)sfKeyNumpad1:
		return ("Pad 1");
	case (unsigned char)sfKeyNumpad2:
		return ("Pad 2");
	case (unsigned char)sfKeyNumpad3:
		return ("Pad 3");
	case (unsigned char)sfKeyNumpad4:
		return ("Pad 4");
	case (unsigned char)sfKeyNumpad5:
		return ("Pad 5");
	case (unsigned char)sfKeyNumpad6:
		return ("Pad 6");
	case (unsigned char)sfKeyNumpad7:
		return ("Pad 7");
	case (unsigned char)sfKeyNumpad8:
		return ("Pad 8");
	case (unsigned char)sfKeyNumpad9:
		return ("Pad 9");
	case (unsigned char)sfKeyF1:
		return ("F1");
	case (unsigned char)sfKeyF2:
		return ("F2");
	case (unsigned char)sfKeyF3:
		return ("F3");
	case (unsigned char)sfKeyF4:
		return ("F4");
	case (unsigned char)sfKeyF5:
		return ("F5");
	case (unsigned char)sfKeyF6:
		return ("F6");
	case (unsigned char)sfKeyF7:
		return ("F7");
	case (unsigned char)sfKeyF8:
		return ("F8");
	case (unsigned char)sfKeyF9:
		return ("F9");
	case (unsigned char)sfKeyF10:
		return ("F10");
	case (unsigned char)sfKeyF11:
		return ("F11");
	case (unsigned char)sfKeyF12:
		return ("F12");
	case (unsigned char)sfKeyF13:
		return ("F13");
	case (unsigned char)sfKeyF14:
		return ("F14");
	case (unsigned char)sfKeyF15:
		return ("F15");
	case (unsigned char)sfKeyPause:
		return ("Pause");
	case 201:
		return ("Joystick Up");
	case 202:
		return ("Joystick Down");
	case 203:
		return ("Joystick Left");
	case 204:
		return ("Joystick Right");
	default:
		if (keyID >= 205)
			return (concatf("Con. Button %i", keyID - 205));
		return (concatf("Key %i", keyID));
	}
}

Button	*loadButtons()
{
	Button		*buttons = NULL;
	int		len = 0;
	int		langs = 0;
	Button_config	config;

	for (; button_config[len].callback; len++);
	for (; game.ressources.languages && game.ressources.languages[langs].name; langs++);
	printf("%s: Loading %i buttons\n", INFO, len + langs + NB_OF_KEYS);
	buttons = malloc(sizeof(*buttons) * (len + langs + NB_OF_KEYS + 1));
	if (!buttons) {
		printf("%s: Couldn't malloc %liB for buttons\n", FATAL, (long)sizeof(*buttons) * (len + langs + NB_OF_KEYS + 1));
		exit(EXIT_FAILURE);
	}
	game.languagesConf.y = langs;
	game.languagesConf.x = len;
	memset(buttons, 0, sizeof(*buttons) * (len + langs + 1));
	for (int i = 0; button_config[i].callback; i++) {
		displayLoadingBar(6, MAX_STEPS, i, len + langs + NB_OF_KEYS, "Creating buttons");
		buttons[i] = create_button(button_config[i], true);
	}
	config.textColor = (sfColor){0, 0, 0, 255};
	config.disabled = false;
	config.color = (sfColor){255, 255, 0, 255};
	config.callback = &changeLanguage;
	for (int i = 0; game.ressources.languages && game.ressources.languages[i].name; i++) {
		displayLoadingBar(6, MAX_STEPS, i + len, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){300 - strlen(game.ressources.languages[i].name) * 7, 50 * i + 10};
		config.size = (sfVector2f){40 + strlen(game.ressources.languages[i].name) * 7, 40};
		buttons[i + len] = create_button(config, false);
		buttons[i + len].content = game.ressources.languages[i].name;
	}
	config.size = (sfVector2f){150, 40};
	config.color = (sfColor){255, 255, 255, 255};
	config.callback = &changeKey;
	for (int i = 0; i < NB_OF_KEYS; i++) {
		displayLoadingBar(6, MAX_STEPS, i + len + langs, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){115 + i / 10 * 272, i % 10 * 48 + 5};
		buttons[i + len + langs] = create_button(config, false);
		buttons[i + len + langs].content = "";
	}
	buttons[len + langs + NB_OF_KEYS].content = NULL;
	printf("%s: Buttons loaded !\n", INFO);
	return (buttons);
}
