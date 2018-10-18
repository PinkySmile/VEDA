#include <SFML/Graphics.h>
#include <stdlib.h>
#include "utils.h"
#include "structs.h"
#include "loading.h"
#include "concatf.h"

void	changeScreenMode(int new)
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	sfVideoMode	mode = {game.settings.windowSize.x, game.settings.windowSize.y, 32};
	sfWindowStyle	style;
	const sfUint8	*icon = NULL;

	game.state.menuSelected = 0;
	if (game.resources.icon.image)
		icon = sfImage_getPixelsPtr(game.resources.icon.image);
	else
		printf("%s: Couldn't load icon image\n", ERROR_BEG);
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window title", 0);
		exit(EXIT_FAILURE);
	}
	if (game.settings.windowMode == new)
		return;
	game.settings.windowMode = new;
	if (game.settings.windowMode == FULLSCREEN) {
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
	} else if (game.settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else
		style = sfTitlebar | sfClose;
	game.settings.baseScale.x = (float)mode.width / 640.0;
	game.settings.baseScale.y = (float)mode.height / 480.0;
	sfRenderWindow_close(game.resources.window);
	sfRenderWindow_destroy(game.resources.window);
	game.resources.window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game.resources.window) {
		printf("%s: Couldn't create window\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window object", 0);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game.resources.window, 32, 32, icon);
	sfRenderWindow_setFramerateLimit(game.resources.window, 60);
}

void	borderless(int buttonID)
{
	(void)buttonID;
	changeScreenMode(BORDERLESS_WINDOW);
}

void	windowed(int buttonID)
{
	(void)buttonID;
	changeScreenMode(WINDOWED);
}

void	fullScreen(int buttonID)
{
	(void)buttonID;
	changeScreenMode(FULLSCREEN);
}
