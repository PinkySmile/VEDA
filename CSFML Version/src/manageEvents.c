#include "structs.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


void	setVolumes(Array sounds, float volume)
{
	sfMusic	**musics = sounds.content;
	
	for (int i = 0; i < sounds.length; i++)
		if (musics[i])
			sfMusic_setVolume(musics[i], volume);
}

void	manageEvents(game_t *game)
{
	sfEvent	event;

	while (sfRenderWindow_pollEvent(game->window, &event)) {
		if (event.type == sfEvtClosed) {
			sfRenderWindow_close(game->window);
			for (int i = 0; i < game->musics.length; i++)
				if (((sfMusic **)game->musics.content)[i] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
					sfMusic_stop(((sfMusic **)game->musics.content)[i]);
		} else if (event.type == sfEvtMouseButtonPressed) {
			manage_mouse_click(game, event.mouseButton);
		} else if (event.type == sfEvtJoystickMoved) {
			printf("%s: Joystick moved to %f arround axis %i on joystick %i\n", INFO, event.joystickMove.position, event.joystickMove.axis, event.joystickMove.joystickId);
			if (game->selected >= 0 && game->menu == 2) {
				for (int i = 0; i < 4; i++) {
					game->settings.keys[i] = 101 + i;
					game->buttons[i + game->languagesConf.y + game->languagesConf.x].content = getKeyString(101 + i);
				}
				game->buttons[game->selected].content = getKeyString(game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x]);
				game->selected = -1;
			}
		} else if (event.type == sfEvtJoystickButtonPressed) {
			printf("%s: Button %i pressed on joystick %i\n", INFO, event.joystickButton.button, event.joystickButton.joystickId);
			if (game->selected >= 0 && game->menu == 2) {
				game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] = event.joystickButton.button + 105;
				game->buttons[game->selected].content = getKeyString(event.joystickButton.button + 105);
				game->selected = -1;
			}
		} else if (event.type == sfEvtKeyPressed) {
			if (game->selected >= 0 && game->menu == 2) {
				game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] = event.key.code;
				game->buttons[game->selected].content = getKeyString(event.key.code);
				game->selected = -1;
			}
		} else if (event.type == sfEvtMouseMoved) {
			if (game->selected == 1 && game->menu == 3) {
				if (event.mouseMove.x <= 140)
					game->settings.sfxVolume = 0;
				else if (event.mouseMove.x >= 440)
					game->settings.sfxVolume = 100;
				else
					game->settings.sfxVolume = (event.mouseMove.x - 140) / 3;
				setVolumes(game->sfx, game->settings.sfxVolume);
			} else if (game->selected == 2 && game->menu == 3) {
				if (event.mouseMove.x <= 140)
					game->settings.musicVolume = 0;
				else if (event.mouseMove.x >= 440)
					game->settings.musicVolume = 100;
				else
					game->settings.musicVolume = (event.mouseMove.x - 140) / 3;
				setVolumes(game->musics, game->settings.musicVolume);
			}
		} else if (event.type == sfEvtMouseButtonReleased) {
			if (game->menu == 3)
				game->selected = -1;
		}
	}
}
