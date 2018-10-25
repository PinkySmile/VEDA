#include <stdlib.h>
#include <memory.h>
#include <structs.h>
#include <utils.h>
#include <loading.h>
#include <concatf.h>
#include <discord_rp.h>
#include <save.h>
#include <callbacks.h>
#include <menus.h>
#include <string.h>

void	debug_keyCommands(sfEvent *event)
{
	char	buffer[100];
	void	*buff;
	long	nbr = random();
	size_t	n = 0;

	if (event->key.code == sfKeyInsert) {
		buff = realloc(game.state.dialogsOnScreen, sizeof(*game.state.dialogsOnScreen) * (game.state.dialogs + 1));
		if (buff) {
			game.state.dialogs++;
			game.state.dialogsOnScreen = buff;
			memset(&game.state.dialogsOnScreen[game.state.dialogs - 1], 0, sizeof(*game.state.dialogsOnScreen));
			game.state.dialogsOnScreen[game.state.dialogs - 1].dialogOwnerName = (
				getCharacter(nbr % (game.state.characters.length + 1)) ?
				NULL :
				getCharacter(nbr % game.state.characters.length)->name
			);
			getline(&game.state.dialogsOnScreen[game.state.dialogs - 1].rawText, &n, stdin);
			game.state.dialogsOnScreen[game.state.dialogs - 1].clock = sfClock_create();
			game.state.dialogsOnScreen[game.state.dialogs - 1].speed = 0.1;
		}

	} else if (event->key.code == sfKeyDelete) {
		for (int i = 0; i < game.state.dialogs; i++) {
			free(game.state.dialogsOnScreen[i].displayedText);
			free(game.state.dialogsOnScreen[i].rawText);
		}
		free(game.state.dialogsOnScreen);
		game.state.dialogsOnScreen = NULL;
		game.state.dialogs = 0;

	} else if (event->key.code == sfKeyHome) {
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
		game.state.menu = BATTLE_MENU;
		if (!getPlayer()) {
			loadGame();
			if (!game.state.loadedMap.objects || !game.state.characters.content) {
				loadLevel("data/levels/test");
				game.state.loadedMap.path = strdup("data/levels/test");
			}
		}
		game.state.battle_infos.boss.movement.pos.x = 100;
		game.state.battle_infos.boss.movement.pos.y = 100;

	} else if (game.debug && event->key.code == sfKeyEqual) {
		for (int i = 0; game.resources.buttons[i].content; i++) {
			game.resources.buttons[i].active = false;
			game.resources.buttons[i].displayed = false;
		}
		memset(game.input.buffer, 0, BUFFER_MAX_SIZE * sizeof(*game.input.buffer));
		game.input.bufSize = BUFFER_MAX_SIZE;
		game.input.bufPos = 0;
		game.state.menu = BUFFER_MODIFIER_MENU;
	}
}

void	manageKeyPressed(sfEvent *event)
{
	int	offset = game.languagesConf.y + game.languagesConf.x;

	if (game.debug)
		debug_keyCommands(event);

	if (
		(game.state.menu == IN_GAME_MENU || game.state.menu == BATTLE_MENU) &&
		game.settings.keys[KEY_PAUSE] == event->key.code
	) {
		backOnTitleScreen(-1);
		saveGame(true);
		return;
	}

	if (
		game.state.menuSelected - offset >= 0 &&
		game.state.menuSelected - offset < 4 &&
		game.state.menu == 2
	)
		for (int i = 0; i < 4; i++)
			if (game.settings.keys[i] >= 201 && game.settings.keys[i] <= 204) {
				game.settings.keys[i] = 255;
				game.resources.buttons[i + offset].content = getKeyString(255);
			}

	if (game.state.menuSelected >= 0 && game.state.menu == 2) {
		game.settings.keys[game.state.menuSelected - offset] = event->key.code;
		game.resources.buttons[game.state.menuSelected].content = getKeyString(event->key.code);
		game.state.menuSelected = -1;
	}
}