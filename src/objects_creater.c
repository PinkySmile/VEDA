#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "utils.h"
#include "macros.h"
#include "concatf.h"
#include "structs.h"

extern char	*programPath;

void	*my_malloc(size_t size)
{
	void	*ptr = malloc(size);

	if (!ptr) {
		//No memory left :/
		printf("%s: Allocation failure (%uB)", FATAL_BEG, size);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

sfText	*createText()
{
	sfText	*text = sfText_create();

	if (!text) {
		printf("%s: Couldn't create text object\n", FATAL_BEG);
		dispMsg("Init error", "Couldn't create text object\n\nClick OK to close the application", 0);
		exit(EXIT_FAILURE);
	}
	return (text);
}

sfRectangleShape	*createRectangleShape()
{
	sfRectangleShape	*rect = sfRectangleShape_create();

	if (!rect) {
		printf("%s: Couldn't create rectangleShape\n", FATAL_BEG);
		dispMsg("Init error", "Couldn't create rectangleShape object\n\nClick OK to close the application", 0);
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
		printf("%s: Couldn't create window\n", FATAL_BEG);
		dispMsg("Init error", "Couldn't create window object\n\nClick OK to close the application", 0);
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
			printf("%s: Couldn't create sprite\n", FATAL_BEG);
			dispMsg("Init error", "Couldn't create sprite object\n\nClick OK to close the application", 0);
			exit(EXIT_FAILURE);
		}
		sfSprite_setTexture(sprite, texture, sfTrue);
	}
	return sprite;
}

char	*getVersion()
{
	int		fd = open("data/version.txt", O_RDONLY);
	static char	version[10];

	printf("%s: Loading version string\n", INFO_BEG);
	if (fd < 0) {
		printf("[ERROR_BEG]: data/version.txt: %s\n", strerror(errno));
		strcpy(version, "?.?.?.?");
		return (version);
	}
	version[read(fd, version, 9)] = 0;
	close(fd);
	for (int i = 0; version[i]; i++)
		if (version[i] == '\n' || version[i] == '\r') {
			version[i] = 0;
			break;
		}
	return (version);
}

sfRenderWindow	*createMainWindow()
{
	char		*title;
	const sfUint8	*icon = NULL;
	sfVideoMode	mode = {640, 480, 32};
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
		mode = sfVideoMode_getDesktopMode();
		break;
	default:
		style = sfTitlebar | sfClose;
		mode.width = game.settings.windowSize.x;
		mode.height = game.settings.windowSize.y;
	}
	game.settings.baseScale.x = (float)mode.width / 640.0;
	game.settings.baseScale.y = (float)mode.height / 480.0;

	//Load the version and create the title and the window
	if (!game.version)
		game.version = getVersion();
	title = concat("VEDA version ", game.version, false, false);
	if (!title) {
		printf("%s: An error occured while creating window title\n", FATAL_BEG);
		dispMsg("Init error", "Couldn't create window title\n\nClick OK to close the application", 0);
		exit(EXIT_FAILURE);
	}
	window = createRenderWindow(mode, title, style, NULL, false);
	free(title);

	//Load the icon and create a sprite out of it
	if (!game.ressources.icon.image)
		game.ressources.icon.image = sfImage_createFromFile(getAbsolutePath("data/icon/icon.png"));
	if (game.ressources.icon.image) {
		if (!game.ressources.icon.texture)
			game.ressources.icon.texture = sfTexture_createFromImage(game.ressources.icon.image, NULL);
		icon = sfImage_getPixelsPtr(game.ressources.icon.image);
	} else
		printf("%s: Couldn't load icon %s\n", ERROR_BEG, getAbsolutePath("data/icon/icon.png"));
	if (icon)
		sfRenderWindow_setIcon(window, 32, 32, icon);
	if (!game.ressources.icon.sprite)
		game.ressources.icon.sprite = createSfSprite(game.ressources.icon.texture);
	return window;
}
