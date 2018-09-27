#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include "configs.h"
#include "structs.h"
#include "macros.h"
#include "display.h"
#include "utils.h"
#include "concatf.h"

Button	createButton(Button_config config, bool createName)
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
		buttons[i] = createButton(button_config[i], true);
	}
	config.textColor = (sfColor){0, 0, 0, 255};
	config.disabled = false;
	config.color = (sfColor){255, 255, 0, 255};
	config.callback = &changeLanguage;
	for (int i = 0; game.ressources.languages && game.ressources.languages[i].name; i++) {
		displayLoadingBar(6, MAX_STEPS, i + len, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){300 - strlen(game.ressources.languages[i].name) * 7, 50 * i + 10};
		config.size = (sfVector2f){40 + strlen(game.ressources.languages[i].name) * 7, 40};
		buttons[i + len] = createButton(config, false);
		buttons[i + len].content = game.ressources.languages[i].name;
	}
	config.size = (sfVector2f){150, 40};
	config.color = (sfColor){255, 255, 255, 255};
	config.callback = &changeKey;
	for (int i = 0; i < NB_OF_KEYS; i++) {
		displayLoadingBar(6, MAX_STEPS, i + len + langs, len + langs + NB_OF_KEYS, "Creating buttons");
		config.pos = (sfVector2f){115 + i / 10 * 272, i % 10 * 48 + 5};
		buttons[i + len + langs] = createButton(config, false);
		buttons[i + len + langs].content = "";
	}
	buttons[len + langs + NB_OF_KEYS].content = NULL;
	printf("%s: Buttons loaded !\n", INFO);
	return (buttons);
}
