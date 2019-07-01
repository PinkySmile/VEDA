#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <concatf.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <destructors.h>
#include <loading.h>
#include <callbacks.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <menus.h>
#include <logger.h>
#include "macros.h"
#include "creators.h"
#include "utils.h"
#include "character.h"
#include "object.h"
#include "game_struct.h"

unsigned	protectedRead(int fd, void *buffer, unsigned size, jmp_buf jump, char *err_buff)
{
	if ((unsigned)read(fd, buffer, size) != size) {
		sprintf(err_buff, "Unexpected EOF (End of file)");
		longjmp(jump, true);
	}
	return size;
}

void	readMagicNumber(int fd, jmp_buf jump, char *err_buff)
{
	unsigned	magic;

	protectedRead(fd, &magic, sizeof(magic), jump, err_buff);
	if (magic == SAVE_FILES_MAGIC_NUMBER_REVERSED) {
		sprintf(
			err_buff,
			"Invalid magic number: The magic is reversed (%x). Did endianness change ?",
			magic
		);
		longjmp(jump, true);
	}
	if (magic != SAVE_FILES_MAGIC_NUMBER) {
		sprintf(
			err_buff,
			"Invalid magic number: The magic number was invalid (%x expected but got %x)",
			SAVE_FILES_MAGIC_NUMBER,
			magic
		);
		longjmp(jump, true);
	}
}

void	readSavedMapVersion(int fd, jmp_buf jump, char *err_buff)
{
	char	head;

	protectedRead(fd, &head, sizeof(head), jump, err_buff);
	if (head < SAVED_LEVEL_VERSION) {
		sprintf(
			err_buff,
			"Invalid header version: Save file has been created with a too old version (Save v%i > Save v%i).",
			SAVED_LEVEL_VERSION,
			head
		);
		longjmp(jump, true);
	} else if (head > SAVED_LEVEL_VERSION) {
		sprintf(
			err_buff,
			"Invalid header version: Client is outdated (Save v%i < Save v%i).",
			SAVED_LEVEL_VERSION,
			head
		);
		longjmp(jump, true);
	}
}

Object	*loadSavedMap(char *path, char **bg)
{
	size_t	len = 0;
	FILE	*stream = fopen(path, "rb");
	int	fd = fileno(stream);
	Object	*map;
	jmp_buf jump;
	char	msg[1024];

	if (setjmp(jump)) {
		logMsg(LOGGER_ERROR, "%s: %s", path, msg);
		close(fd);
		return NULL;
	}

	readMagicNumber(fd, jump, msg);
	readSavedMapVersion(fd, jump, msg);
	protectedRead(fd, &len, sizeof(len), jump, msg);
	*bg = protectedMalloc(len + 1);
	(*bg)[protectedRead(fd, *bg, len, jump, msg)] = 0;
	protectedRead(fd, &len, sizeof(len), jump, msg);
	map = protectedMalloc((len + 1) * sizeof(*map));
	protectedRead(fd, map, len * sizeof(*map), jump, msg);
	map[len].layer = 0;
	protectedRead(fd, &game.state.characters.length, sizeof(game.state.characters.length), jump, msg);
	game.state.characters.content = protectedMalloc(sizeof(Character) * game.state.characters.length);
	protectedRead(fd, game.state.characters.content, sizeof(Character) * game.state.characters.length, jump, msg);
	for (int i = 0; i < game.state.characters.length; i++) {
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			getCharacter(i)->damageClock[j] = sfClock_create();
		getCharacter(i)->movement.animationClock = sfClock_create();
		getCharacter(i)->movement.stateClock = sfClock_create();
		getCharacter(i)->stats.energyRegenClock = sfClock_create();
		getCharacter(i)->inventory.content = protectedMalloc(getCharacter(i)->inventory.length);
		protectedRead(
			fd,
			getCharacter(i)->inventory.content,
			getCharacter(i)->inventory.length * sizeof(Item),
			jump,
			msg
		);
	}
	return (map);
}

bool	loadGame()
{
	FILE		*stream;
	int		fd = -1;
	char		*buffer;
	unsigned int	len = 0;
	struct	stat	st;
	jmp_buf		jump;
	char		msg[1024];

	logMsg(LOGGER_INFO, "Loading game");
	if (setjmp(jump)) {
		logMsg(LOGGER_ERROR, "Corrupted save file detected: %s", msg);
		close(fd);
		return dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) != IDYES;
	}

	stream = fopen("save/game.dat", "rb");
	if (!stream) {
		logMsg(LOGGER_ERROR, "Cannot open save file (save/game.dat: %s)", strerror(errno));
		return false;
	}
	fd = fileno(stream);
	free(game.state.loadedMap.objects);
	free(game.state.loadedMap.backgroundPath);
	free(game.state.loadedMap.path);

	readMagicNumber(fd, jump, msg);
	game.state.loadedMap.objects = NULL;
	if (read(fd, &len, sizeof(len)) != sizeof(len)) {
		sprintf(msg, "Unexpected <EOF>");
		longjmp(jump, true);
	}
	game.state.loadedMap.path = protectedMalloc(len + 1);
	if ((unsigned)read(fd, game.state.loadedMap.path, len) != len) {
		sprintf(msg, "Unexpected <EOF>");
		longjmp(jump, true);
	} else {
		game.state.loadedMap.path[len] = 0;
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		if (stat(buffer, &st) != -1) {
			free(game.state.loadedMap.objects);
			destroyCharacters();
			game.state.loadedMap.objects = loadSavedMap(buffer, &game.state.loadedMap.backgroundPath);
			if (!game.state.loadedMap.objects || !game.state.characters.content) {
				sprintf(msg, "Saved map has invalid data");
				longjmp(jump, true);
			}
		} else if (stat(game.state.loadedMap.path, &st) != -1) {
			loadLevel(game.state.loadedMap.path);
			if (!game.state.loadedMap.objects || !game.state.characters.content) {
				sprintf(msg, "Saved map has invalid data");
				longjmp(jump, true);
			}
			getCharacter(0)->isPlayer = true;
		} else {
			sprintf(msg, "Saved map wasn't found");
			longjmp(jump, true);
		}
		free(buffer);
	}
	close(fd);
	logMsg(LOGGER_INFO, "Save file loaded !");
	return true;
}
