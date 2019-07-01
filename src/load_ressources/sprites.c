#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "configs.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <logger.h>

Sprite	createSprite(Sprite_config config)
{
	Sprite	sprite = {NULL, NULL, {0, 0}, {0, 0, 0, 0}};

	logMsg(LOGGER_DEBUG, "Loading file %s", config.path);
	sprite.texture = sfTexture_createFromFile(config.path, NULL);
	if (sprite.texture) {
		sprite.sprite = sfSprite_create();
		if (!sprite.sprite) {
			sfTexture_destroy(sprite.texture);
			logMsg(LOGGER_ERROR, "Couldn't create sprite object for %s", config.path);
			return ((Sprite){NULL, NULL, {0, 0}, {0, 0, 0, 0}});
		}
		sfSprite_setTexture(sprite.sprite, sprite.texture, sfTrue);
		sprite.rect.left = config.rectPos.x;
		sprite.rect.top = config.rectPos.y;
		sprite.rect.width = config.size.x;
		sprite.rect.height = config.size.y;
		sprite.size.x = config.size.x;
		sprite.size.y = config.size.y;
	} else
		logMsg(LOGGER_ERROR, "Couldn't load file %s", config.path);
	return (sprite);
}

Array	loadSprites()
{
	Array	array = {NULL, 0};
	int	len = 0;
	Sprite	*sprites = NULL;

	for (; sprites_conf[len].path; len++);
	logMsg(LOGGER_INFO, "Loading %i textures", len);
	sprites = malloc(sizeof(*sprites) * len);
	if (!sprites) {
		logMsg(LOGGER_FATAL, "Couldn't allocate %liB of memory", (long)sizeof(*sprites) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = sprites;
	for (int i = 0; sprites_conf[i].path; i++) {
		displayLoadingBar(2, MAX_STEPS, i, len, "Loading textures");
		sprites[i] = createSprite(sprites_conf[i]);
	}
	logMsg(LOGGER_INFO, "Textures loaded !");
	return (array);
}
