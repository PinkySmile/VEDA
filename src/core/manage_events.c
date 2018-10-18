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
	int	random = rand();

	while (sfRenderWindow_pollEvent(game.resources.window, &event)) {
		if (event.type == sfEvtClosed) {
			sfRenderWindow_close(game.resources.window);
			if (game.state.menu == 1 || game.state.menu == 7)
				saveGame(true);
			for (int i = 0; i < game.resources.musics.length; i++)
				if (((sfMusic **)game.resources.musics.content)[i] && sfMusic_getStatus(((sfMusic **)game.resources.musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
					sfMusic_stop(((sfMusic **)game.resources.musics.content)[i]);
		} else if (event.type == sfEvtTextEntered) {
			if (event.text.unicode == 8 && game.input.bufPos > 0)
				game.input.buffer[--game.input.bufPos] = 0;
			else if (event.text.unicode != 8)
				game.input.buffer[game.input.bufPos < game.input.bufSize ? game.input.bufPos++ : game.input.bufPos - 1] = event.text.unicode;
		} else if (event.type == sfEvtMouseButtonPressed) {
			manage_mouse_click(event.mouseButton);
		} else if (event.type == sfEvtJoystickMoved) {
			if (event.joystickMove.position < 3 && event.joystickMove.position > -3)
				continue;
			if (game.state.menuSelected - game.languagesConf.y - game.languagesConf.x >= 0 && game.state.menuSelected - game.languagesConf.y - game.languagesConf.x < 4 && game.state.menu == 2) {
				for (int i = 0; i < 4; i++) {
					game.settings.keys[i] = 201 + i;
					game.resources.buttons[i + game.languagesConf.y + game.languagesConf.x].content = getKeyString(201 + i);
				}
				game.resources.buttons[game.state.menuSelected].content = getKeyString(game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x]);
				game.state.menuSelected = -1;
			}
		} else if (event.type == sfEvtJoystickButtonPressed) {
			if ((game.state.menu == 1 || game.state.menu == 7) && game.settings.keys[KEY_PAUSE] == event.joystickButton.button + 205) {
				backOnTitleScreen(-1);
				saveGame(true);
				continue;
			}
			if (game.state.menuSelected - game.languagesConf.y - game.languagesConf.x >= 0 && game.state.menuSelected - game.languagesConf.y - game.languagesConf.x < 4 && game.state.menu == 2)
				for (int i = 0; i < 4; i++)
					if (game.settings.keys[i] >= 201 && game.settings.keys[i] <= 204) {
						for (int i = 0; i < 4; i++) {
							game.settings.keys[i] = -1;
							game.resources.buttons[i + game.languagesConf.y + game.languagesConf.x].content = getKeyString(-1);
						}
						break;
					}
			if (game.state.menuSelected >= 0 && game.state.menu == 2) {
				game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] = event.joystickButton.button + 205;
				game.resources.buttons[game.state.menuSelected].content = getKeyString(event.joystickButton.button + 205);
				game.state.menuSelected = -1;
			}
		} else if (event.type == sfEvtKeyPressed) {
			if (game.debug && event.key.code == sfKeyInsert) {
				void	*buff = realloc(game.state.dialogsOnScreen, sizeof(*game.state.dialogsOnScreen) * (game.state.dialogs + 1));
				size_t	n = 0;

				if (buff) {
					game.state.dialogs++;
					game.state.dialogsOnScreen = buff;
					memset(&game.state.dialogsOnScreen[game.state.dialogs - 1], 0, sizeof(*game.state.dialogsOnScreen));
					game.state.dialogsOnScreen[game.state.dialogs - 1].dialogOwnerName = (random % (game.state.characters.length + 1) == game.state.characters.length ? NULL : ((Character *)game.state.characters.content)[random].name);
					getline(&game.state.dialogsOnScreen[game.state.dialogs - 1].rawText, &n, stdin);
					game.state.dialogsOnScreen[game.state.dialogs - 1].clock = sfClock_create();
					game.state.dialogsOnScreen[game.state.dialogs - 1].speed = 0.1;
				}
			} else if (game.debug && event.key.code == sfKeyDelete) {
				for (int i = 0; i < game.state.dialogs; i++) {
					free(game.state.dialogsOnScreen[i].displayedText);
					free(game.state.dialogsOnScreen[i].rawText);
				}
				free(game.state.dialogsOnScreen);
				game.state.dialogsOnScreen = NULL;
				game.state.dialogs = 0;
			}
			if (/*game.debug &&*/ event.key.code == sfKeyHome) {
				char	buffer[100];
				char	*buff;

				memset(buffer, 0, 100);
				for (int i = 0; game.input.buffer[i]; i++)
					buffer[i] = game.input.buffer[i] % 255;
				game.state.battle_infos = loadBattleScript(/*buffer*/"data/battles/alexandre/battle_normal/info_file.json");
				for (int i = 0; game.resources.buttons[i].content; i++) {
					game.resources.buttons[i].active = false;
					game.resources.buttons[i].displayed = false;
				}
				buff = concatf("Fighting %s (%s)", game.state.battle_infos.boss.name, game.state.battle_infos.name);
				updateDiscordPresence("In Game", buff, 0, false, "icon", NULL, "VEDA", NULL);
				free(buff);
				game.state.menu = 7;
				if (!getPlayer(game.state.characters.content, game.state.characters.length)) {
					loadGame();
					if (!game.state.loadedMap.objects || !game.state.characters.content) {
						loadLevel("data/levels/test");
						game.state.loadedMap.path = strdup("data/levels/test");
					}
				}
				game.state.battle_infos.boss.movement.pos.x = 100;
				game.state.battle_infos.boss.movement.pos.y = 100;
			}
			if (game.debug && event.key.code == sfKeyEqual) {
				for (int i = 0; game.resources.buttons[i].content; i++) {
					game.resources.buttons[i].active = false;
					game.resources.buttons[i].displayed = false;
				}
				memset(game.input.buffer, 0, BUFFER_MAX_SIZE * sizeof(*game.input.buffer));
				game.input.bufSize = BUFFER_MAX_SIZE;
				game.input.bufPos = 0;
				game.state.menu = 5;
				continue;
			}
			if ((game.state.menu == 1 || game.state.menu == 7) && game.settings.keys[KEY_PAUSE] == event.key.code) {
				backOnTitleScreen(-1);
				saveGame(true);
				continue;
			}
			if (game.state.menuSelected - game.languagesConf.y - game.languagesConf.x >= 0 && game.state.menuSelected - game.languagesConf.y - game.languagesConf.x < 4 && game.state.menu == 2)
				for (int i = 0; i < 4; i++)
					if (game.settings.keys[i] >= 201 && game.settings.keys[i] <= 204) {
						for (int i = 0; i < 4; i++) {
							game.settings.keys[i] = -1;
							game.resources.buttons[i + game.languagesConf.y + game.languagesConf.x].content = getKeyString(-1);
						}
						break;
					}
			if (game.state.menuSelected >= 0 && game.state.menu == 2) {
				game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] = event.key.code;
				game.resources.buttons[game.state.menuSelected].content = getKeyString(event.key.code);
				game.state.menuSelected = -1;
			}
		} else if (event.type == sfEvtMouseMoved) {
			if (game.state.menuSelected == 1 && game.state.menu == 3) {
				if (event.mouseMove.x <= 140)
					game.settings.sfxVolume = 0;
				else if (event.mouseMove.x >= 440)
					game.settings.sfxVolume = 100;
				else
					game.settings.sfxVolume = (event.mouseMove.x - 140) / 3;
				setVolumes(game.resources.sfx, game.settings.sfxVolume);
				if (((sfMusic **)game.resources.sfx.content)[DIRT1 + random % 4])
					sfMusic_play(((sfMusic **)game.resources.sfx.content)[DIRT1 + random % 4]);
			} else if (game.state.menuSelected == 2 && game.state.menu == 3) {
				if (event.mouseMove.x <= 140)
					game.settings.musicVolume = 0;
				else if (event.mouseMove.x >= 440)
					game.settings.musicVolume = 100;
				else
					game.settings.musicVolume = (event.mouseMove.x - 140) / 3;
				setVolumes(game.resources.musics, game.settings.musicVolume);
			}
		} else if (event.type == sfEvtMouseButtonReleased) {
			if (game.state.menu == 3)
				game.state.menuSelected = -1;
		}
	}
}
