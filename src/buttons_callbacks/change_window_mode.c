#include <SFML/Graphics.h>
#include <stdlib.h>
#include "utils.h"
#include "structs.h"
#include "loading.h"
#include "concatf.h"

void	changeScreenMode(enum windowMode new)
{
	char		*title = concat("VEDA version ", getVersion(), false, false);
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
		dispMsg("Window error", "Couldn't create window title", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (game.settings.windowMode == new)
		return;
	game.settings.windowMode = new;
	switch (new) {
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
	game.settings.windowSize = game.newSize;
	game.settings.baseScale = (sfVector2f){game.newSize.x / 640., game.newSize.y / 480.};
	sfRenderWindow_setSize(game.resources.window, game.newSize);
	if (game.resources.view)
		sfView_destroy(game.resources.view);
	game.resources.view = sfView_createFromRect((sfFloatRect){0, 0, game.newSize.x, game.newSize.y});
	sfRenderWindow_setView(game.resources.window, game.resources.view);
}

void	borderless(int buttonID)
{
	(void)buttonID;
	changeScreenMode(BORDERLESS_WINDOW);
	game.resources.buttons[15].active = false;
	game.resources.buttons[15].displayed = false;
}

void	windowed(int buttonID)
{
	(void)buttonID;
	changeScreenMode(WINDOWED);
	game.resources.buttons[15].active = true;
	game.resources.buttons[15].displayed = true;
}

void	fullScreen(int buttonID)
{
	(void)buttonID;
	changeScreenMode(FULLSCREEN);
	game.resources.buttons[15].active = false;
	game.resources.buttons[15].displayed = false;
}
