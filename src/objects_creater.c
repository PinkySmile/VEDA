#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <logger.h>
#include "utils.h"
#include "macros.h"
#include "concatf.h"
#include "structs.h"

extern char	*programPath;

void	*protectedMalloc(size_t size)
{
	void	*ptr = malloc(size);

	if (!ptr) {
		//No memory left :/
		logMsg(LOGGER_FATAL, "Allocation failure (%luB)", (long unsigned int)size);
		dispMsg("Memory allocation error", ALLOC_ERROR_MSG, MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

sfText	*createText()
{
	sfText	*text = sfText_create();

	if (!text) {
		logMsg(LOGGER_FATAL, "Couldn't create text object");
		dispMsg("Init error", "Couldn't create text object\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	return (text);
}

sfSound	*createSound()
{
	sfSound	*sound = sfSound_create();

	if (!sound) {
		logMsg(LOGGER_FATAL, "Couldn't create sound object");
		dispMsg("Init error", "Couldn't create sound object\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	return (sound);
}

sfRectangleShape	*createRectangleShape()
{
	sfRectangleShape	*rect = sfRectangleShape_create();

	if (!rect) {
		logMsg(LOGGER_FATAL, "Couldn't create rectangleShape");
		dispMsg("Init error", "Couldn't create rectangleShape object\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	return (rect);
}

sfRenderWindow	*createRenderWindow(sfVideoMode mode, const void *title, sfUint32 style, const sfContextSettings *settings, bool unicode)
{
	sfRenderWindow	*window;

	if (unicode)
		window = sfRenderWindow_createUnicode(mode, title, style, settings);
	else
		window = sfRenderWindow_create(mode, title, style, settings);
	if (!window) {
		//The window cannot be created, get out of here
		logMsg(LOGGER_FATAL, "Couldn't create window");
		dispMsg("Init error", "Couldn't create window object\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	return window;
}

sfSprite	*createSfSprite(sfTexture *texture)
{
	sfSprite	*sprite = NULL;

	if (texture) {
		sprite = sfSprite_create();
		if (!sprite) {
			logMsg(LOGGER_FATAL, "Couldn't create sprite");
			dispMsg("Init error", "Couldn't create sprite object\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
		sfSprite_setTexture(sprite, texture, sfTrue);
	}
	return sprite;
}

void loadVersion()
{
	FILE	*stream = fopen("data/version.txt", "rb");
	char	*line = NULL;
	size_t	n = 0;

	logMsg(LOGGER_DEBUG, "Loading version string");
	if (!stream) {
		logMsg(LOGGER_ERROR, "data/version.txt: %s", strerror(errno));
		strcpy(game.version, "?.?.?");
		return;
	}
	getline(&line, &n, stream);
	fclose(stream);
	if (!line) {
		logMsg(LOGGER_ERROR, "Cannot get version");
		strcpy(game.version, "?.?.?");
		return;
	}
	while (strlen(line) && (line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r'))
		line[strlen(line) - 1] = 0;
	strcpy(game.version, line);
	free(line);
}

sfRenderWindow	*createMainWindow()
{
	char		*title;
	const sfUint8	*icon = NULL;
	sfVideoMode	mode = {game.settings.windowSize.x, game.settings.windowSize.y, 32};
	sfWindowStyle	style;
	sfRenderWindow	*window;

	//Get the scaling and the window style from loaded settings
	switch (game.settings.windowMode) {
	case FULLSCREEN:
		style = sfFullscreen;
			mode = sfVideoMode_getDesktopMode();
		break;
	case BORDERLESS_WINDOW:
		style = sfNone;
		break;
	default:
		style = sfTitlebar | sfClose;
		game.settings.windowMode = WINDOWED;
	}

	game.settings.baseScale.x = (float)mode.width / 640;
	game.settings.baseScale.y = (float)mode.height / 480;

	//Load the version and create the title and the window
	title = concat("VEDA version ", game.version, false, false);
	if (!title) {
		logMsg(LOGGER_FATAL, "An error occured while creating window title");
		dispMsg("Init error", "Couldn't create window title\n\nClick OK to close the application", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	window = createRenderWindow(mode, title, style, NULL, false);
	free(title);

	//Load the icon and create a sprite out of it
	if (!game.resources.icon.image)
		game.resources.icon.image = sfImage_createFromFile(getAbsolutePath("data/icon/icon.png"));
	if (game.resources.icon.image) {
		if (!game.resources.icon.texture)
			game.resources.icon.texture = sfTexture_createFromImage(game.resources.icon.image, NULL);
		icon = sfImage_getPixelsPtr(game.resources.icon.image);
	} else
		logMsg(LOGGER_ERROR, "Couldn't load icon %s", getAbsolutePath("data/icon/icon.png"));
	if (icon)
		sfRenderWindow_setIcon(window, 32, 32, icon);
	if (!game.resources.icon.sprite)
		game.resources.icon.sprite = createSfSprite(game.resources.icon.texture);

	//Grab the cursor
	sfRenderWindow_setMouseCursorGrabbed(window, game.settings.windowMode != WINDOWED);
	return window;
}
