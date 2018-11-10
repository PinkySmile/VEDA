#include <SFML/Graphics.h>
#include <stdlib.h>
#include "utils.h"
#include "structs.h"
#include "loading.h"
#include "concatf.h"

void	changeScreenMode(enum windowMode new, sfVector2u newSize)
{
	char		*title = concat("VEDA version ", getVersion(), false, false);
	sfVideoMode	mode = {newSize.x, newSize.y, 32};
	sfWindowStyle	style;
	const sfUint8	*icon = NULL;

	game.state.menuSelected = 0;
	if (game.resources.icon.image)
		icon = sfImage_getPixelsPtr(game.resources.icon.image);
	else
		printf("%s: Couldn't load icon image\n", ERROR_BEG);
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window title", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}

	//Check if the window needs to be changed
	if (
		game.settings.windowMode == new && (
			(game.settings.windowSize.x == newSize.x && game.settings.windowSize.y == newSize.y) ||
			new == FULLSCREEN
		)
	)
		return;

	game.settings.windowSize = newSize;
	game.settings.windowMode = new;

	switch (new) {
	case FULLSCREEN:
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
		break;
	case BORDERLESS_WINDOW:
		style = sfNone;
		break;
	default:
		style = sfTitlebar | sfClose;
	}

	game.settings.baseScale.x = (float)mode.width / 640.0;
	game.settings.baseScale.y = (float)mode.height / 480.0;
	sfRenderWindow_close(game.resources.window);
	sfRenderWindow_destroy(game.resources.window);
	game.resources.window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game.resources.window) {
		printf("%s: Couldn't create window\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window object", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game.resources.window, 32, 32, icon);
	sfRenderWindow_setFramerateLimit(game.resources.window, 60);
}

void	applyNewWindowSize(int buttonID)
{
	(void)buttonID;
	changeScreenMode(game.newMode, game.newSize);
}

void	borderless(int buttonID)
{
	(void)buttonID;
	game.newMode = BORDERLESS_WINDOW;
}

void	windowed(int buttonID)
{
	(void)buttonID;
	game.newMode = WINDOWED;
}

void	fullScreen(int buttonID)
{
	(void)buttonID;
	game.newMode = FULLSCREEN;
}
