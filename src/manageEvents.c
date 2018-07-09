#include "structs.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <battle_api.h>


void	setVolumes(Array sounds, float volume)
{
	sfMusic	**musics = sounds.content;

	for (int i = 0; i < sounds.length; i++)
		if (musics[i])
			sfMusic_setVolume(musics[i], volume);
}

void	manageEvents(game_t *game)
{
	sfEvent		event;
	int		random = rand();
	static int	var = 0;

	while (sfRenderWindow_pollEvent(game->window, &event)) {
		if (event.type == sfEvtClosed) {
			sfRenderWindow_close(game->window);
			if (game->menu == 1 || game->menu == 7)
				saveGame(game, true);
			for (int i = 0; i < game->musics.length; i++)
				if (((sfMusic **)game->musics.content)[i] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
					sfMusic_stop(((sfMusic **)game->musics.content)[i]);
		} else if (event.type == sfEvtTextEntered) {
			if (event.text.unicode == 8 && game->bufPos > 0)
				game->buffer[--game->bufPos] = 0;
			else if (event.text.unicode != 8)
				game->buffer[game->bufPos < game->bufSize ? game->bufPos++ : game->bufPos - 1] = event.text.unicode;
		} else if (event.type == sfEvtMouseButtonPressed) {
			manage_mouse_click(game, event.mouseButton);
		} else if (event.type == sfEvtJoystickMoved) {
			if (event.joystickMove.position < 3 && event.joystickMove.position > -3)
				continue;
			if (game->selected - game->languagesConf.y - game->languagesConf.x >= 0 && game->selected - game->languagesConf.y - game->languagesConf.x < 4 && game->menu == 2) {
				for (int i = 0; i < 4; i++) {
					game->settings.keys[i] = 201 + i;
					game->buttons[i + game->languagesConf.y + game->languagesConf.x].content = getKeyString(201 + i);
				}
				game->buttons[game->selected].content = getKeyString(game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x]);
				game->selected = -1;
			}
		} else if (event.type == sfEvtJoystickButtonPressed) {
			if ((game->menu == 1 || game->menu == 7) && game->settings.keys[KEY_PAUSE] == event.joystickButton.button + 205) {
				back_on_title_screen(game, -1);
				saveGame(game, true);
				continue;
			}
			if (game->selected - game->languagesConf.y - game->languagesConf.x >= 0 && game->selected - game->languagesConf.y - game->languagesConf.x < 4 && game->menu == 2)
				for (int i = 0; i < 4; i++)
					if (game->settings.keys[i] >= 201 && game->settings.keys[i] <= 204) {
						for (int i = 0; i < 4; i++) {
							game->settings.keys[i] = -1;
							game->buttons[i + game->languagesConf.y + game->languagesConf.x].content = getKeyString(-1);
						}
						break;
					}
			if (game->selected >= 0 && game->menu == 2) {
				game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] = event.joystickButton.button + 205;
				game->buttons[game->selected].content = getKeyString(event.joystickButton.button + 205);
				game->selected = -1;
			}
		} else if (event.type == sfEvtKeyPressed) {
			if (game->debug && event.key.code == sfKeyInsert) {
				printf("%s: Adding projectile %i %i\n", INFO, var, game->battle_infos.projectileBank.length);
				addProjectile(var, game->battle_infos.boss.movement.pos.x, game->battle_infos.boss.movement.pos.y - 50, -1, 0);
				var = var < game->battle_infos.projectileBank.length - 1 ? var + 1 : 0;
			}
			if (game->debug && event.key.code == sfKeyHome) {
				char	buffer[100];
				Array	buff = game->battle_infos.projectiles;

				memset(buffer, 0, 100);
				for (int i = 0; game->buffer[i]; i++)
					buffer[i] = game->buffer[i] % 255;
				game->battle_infos = loadBattleScript(/*buffer*/"data/battles/alexandre/battle_normal/info_file.json");
				game->battle_infos.projectiles = buff;
				for (int i = 0; game->buttons[i].content; i++) {
					game->buttons[i].active = false;
					game->buttons[i].displayed = false;
				}
				game->menu = 7;
				if (!getPlayer(game->characters.content, game->characters.length)) {
					loadGame(game);
					if (!game->map || !game->characters.content) {
						loadLevel("data/levels/test", game);
						game->loadedMap = strdup("data/levels/test");
					}
				}
				game->battle_infos.boss.movement.pos.x = 100;
				game->battle_infos.boss.movement.pos.y = 100;
			}
			if (game->debug && event.key.code == sfKeyEqual) {
				for (int i = 0; game->buttons[i].content; i++) {
					game->buttons[i].active = false;
					game->buttons[i].displayed = false;
				}
				memset(game->buffer, 0, BUFFER_MAX_SIZE * sizeof(*game->buffer));
				game->bufSize = BUFFER_MAX_SIZE;
				game->bufPos = 0;
				game->menu = 5;
				continue;
			}
			if ((game->menu == 1 || game->menu == 7) && game->settings.keys[KEY_PAUSE] == event.key.code) {
				back_on_title_screen(game, -1);
				saveGame(game, true);
				continue;
			}
			if (game->selected - game->languagesConf.y - game->languagesConf.x >= 0 && game->selected - game->languagesConf.y - game->languagesConf.x < 4 && game->menu == 2)
				for (int i = 0; i < 4; i++)
					if (game->settings.keys[i] >= 201 && game->settings.keys[i] <= 204) {
						for (int i = 0; i < 4; i++) {
							game->settings.keys[i] = -1;
							game->buttons[i + game->languagesConf.y + game->languagesConf.x].content = getKeyString(-1);
						}
						break;
					}
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
				if (((sfMusic **)game->sfx.content)[DIRT1 + random % 4])
					sfMusic_play(((sfMusic **)game->sfx.content)[DIRT1 + random % 4]);
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
