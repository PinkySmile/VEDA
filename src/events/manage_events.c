#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include "loading.h"
#include "structs.h"
#include "functions.h"
#include "discord_rp.h"
#include "concatf.h"
#include "save.h"
#include "events.h"
#include "menus.h"
#include "utils.h"
#include "battle_lua.h"

void	setVolumes(Array sounds, float volume)
{
	sfMusic	**musics = sounds.content;

	for (int i = 0; i < sounds.length; i++)
		if (musics[i])
			sfMusic_setVolume(musics[i], volume);
}

void	manageEvents()
{
	sfEvent	event;

	while (sfRenderWindow_pollEvent(game.resources.window, &event)) {
		if (event.type == sfEvtClosed)
			manageEventClosed();
		else if (event.type == sfEvtTextEntered)
			manageTextEntered(&event);
		else if (event.type == sfEvtMouseButtonPressed)
			manageMouseClick(event.mouseButton);
		else if (event.type == sfEvtJoystickMoved)
			manageJoystickMoved();
		else if (event.type == sfEvtJoystickButtonPressed)
			manageJoystickButtonPressed(&event);
		else if (event.type == sfEvtKeyPressed)
			manageKeyPressed(&event);
		else if (event.type == sfEvtMouseMoved)
			manageMouseMoved(&event);
		else if (event.type == sfEvtMouseButtonReleased)
			manageMouseReleased();
	}
}
