#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <callbacks.h>
#include <logger.h>
#include "destructors.h"
#include "creators.h"
#include "utils.h"
#include "loading.h"
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "concatf.h"

void	saveLevel(char *path, Object *objs, char *header, Array characters)
{
	FILE		*stream;
	size_t		len;
	int		fd;
	int		magic = SAVE_FILES_MAGIC_NUMBER;
	char		ver = SAVED_LEVEL_VERSION;
	char		*buffer;
	Character	*chars = characters.content;

	logMsg(LOGGER_INFO, "Saving to %s",  path);
	stream = fopen(path, "wb");
	if (!stream) {
		buffer = concatf("Cannot open save file (%s: %s)", path, strerror(errno));
		logMsg(LOGGER_ERROR, "%s", buffer);
		dispMsg("Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return;
	}
	fd = fileno(stream);
	len = strlen(header);
	write(fd, &magic, sizeof(magic));
	write(fd, &ver, sizeof(ver));
	write(fd, &len, sizeof(len));
	write(fd, header, len);
	for (len = 0; objs[len].layer; len++);
	write(fd, &len, sizeof(len));
	write(fd, objs, sizeof(*objs) * len);
	write(fd, &characters.length, sizeof(characters.length));
	write(fd, chars, sizeof(Character) * characters.length);
	for (int i = 0; i < characters.length; i++)
		write(
			fd,
			chars[i].inventory.content,
			chars[i].inventory.length * sizeof(Item)
		);
	fclose(stream);
}

bool	saveGame(bool level)
{
	int		fd;
	struct stat	st;
	bool		success;
	int		magic = SAVE_FILES_MAGIC_NUMBER;
	int		len = 0;
	char		*buffer = NULL;

	logMsg(LOGGER_INFO, "Saving game");
	if (stat("save", &st) == -1) {
		logMsg(LOGGER_INFO, "Creating folder \"save\"");
		#if defined _WIN32 || defined __WIN32 || defined __WIN32__
			success = (mkdir("save") == 0);
		#else
			success = (mkdir("save", 0766) == 0);
		#endif
		if (!success) {
			buffer = concatf("Couldn't create folder \"save\" (%s)", strerror(errno));
			logMsg(LOGGER_ERROR, "%s", buffer);
			dispMsg("Error", buffer, MB_YESNO | MB_ICONERROR);
			free(buffer);
			return (false);
		}
	}
	remove("save/game.dat.old");
	rename("save/game.dat", "save/game.dat.old");
	fd = open("save/game.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		buffer = concatf("Cannot open save file (save/game.dat: %s)\n", strerror(errno));
		logMsg(LOGGER_ERROR, "%s", buffer);
		dispMsg("Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return (false);
	}
	len = game.state.loadedMap.path ? strlen(game.state.loadedMap.path) : 0;
	if (write(fd, &magic, sizeof(magic)) != sizeof(magic) || write(fd, &len, sizeof(len)) != sizeof(len) || write(fd, game.state.loadedMap.path, len) != len) {
		logMsg(LOGGER_ERROR, "Couldn't write save file");
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", MB_OK | MB_ICONERROR);
		return (false);
	}
	close(fd);
	if (level) {
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		remove(buffer);
		saveLevel(buffer, game.state.loadedMap.objects, game.state.loadedMap.backgroundPath, game.state.characters);
		free(buffer);
	}
	return (true);
}
