#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "concatf.h"

void	saveLevel(char *path, Object *objs, char *header)
{
	int	fd;
	char	*buffer = "test";

	printf("%s: Saving to %s\n", INFO, path);
	fd = open(path, O_WRONLY | O_CREAT, 0664);
	if (fd < 0) {
		printf("%s: Cannot open save file (%s: %s)\n", ERROR, buffer, strerror(errno));
		buffer = concatf("Cannot open save file (%s: %s)\n", buffer, strerror(errno));
		dispMsg("Error", buffer, 0);
		free(buffer);
		return;
	}
	write(fd, header, strlen(header));
	for (int i = 0; objs[i].layer; i++) {
		buffer = concatf("\n%i %i %i %i %i %i %f %i %i %i %i %i %i %i %i %i",
			objs[i].id,
			objs[i].pos.x,
			objs[i].pos.y,
			objs[i].layer,
			objs[i].solid,
			objs[i].action,
			objs[i].invulnerabiltyTime,
			objs[i].footstepSound,
			objs[i].footstepVariance,
			objs[i].damages[0],
			objs[i].damages[1],
			objs[i].damages[2],
			objs[i].damages[3],
			objs[i].damages[4],
			objs[i].damages[5],
			objs[i].damages[6]
		);
		write(fd, buffer, strlen(buffer));
		free(buffer);
	}
	close(fd);
}

bool	saveGame(game_t *game, bool level)
{
	int		fd;
	struct stat	st;
	bool		success = false;
	Character	player = *getPlayer(game->characters.content, game->characters.length);
	int		len = 0;
	char		*buffer = NULL;

	printf("%s: Saving game\n", INFO);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO);
		#ifdef __MINGW32__
			success = (mkdir("save") == 0);
		#else
			success = (mkdir("save", 0766) == 0);
		#endif
		if (!success) {
			printf("%s: Counldn't create folder \"save\" (%s)\n", ERROR, strerror(errno));
			buffer = concatf("Counldn't create folder \"save\" (%s)", strerror(errno));
			dispMsg("Error", buffer, 4);
			free(buffer);
			return (false);
		}
	}
	remove("save/game.dat.old");
	rename("save/game.dat", "save/game.dat.old");
	fd = open("save/game.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR, strerror(errno));
		buffer = concatf("Cannot open save file (save/game.dat: %s)\n", strerror(errno));
		dispMsg("Error", buffer, 0);
		free(buffer);
		return (false);
	}
	player.movement.animationClock = NULL;
	player.movement.stateClock = NULL;
	player.stats.energyRegenClock = NULL;
	if (write(fd, &player, sizeof(player)) != sizeof(player)) {
		printf("%s: Couldn't write save file\n", ERROR);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	if (write(fd, &game->characterChosed, sizeof(game->characterChosed)) != sizeof(game->characterChosed)) {
		printf("%s: Couldn't write save file\n", ERROR);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	len = game->loadedMap ? strlen(game->loadedMap) : 0;
	if (write(fd, &len, sizeof(len)) != sizeof(len)) {
		printf("%s: Couldn't write save file\n", ERROR);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	if (write(fd, game->loadedMap,len) != len) {
		printf("%s: Couldn't write save file\n", ERROR);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	close(fd);
	if (level) {
		buffer = concat(game->loadedMap, ".sav", false, false);
		remove(buffer);
		saveLevel(buffer, game->map, game->bg);
		free(buffer);
	}
	return (true);
}

void	loadGame(game_t *game)
{
	int		fd;
	Character	player;
	bool		use = false;
	char		*buffer;
	int		len = 0;
	struct stat	st;

	printf("%s: Loading game\n", INFO);
	fd = open("save/game.dat", O_RDONLY);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR, strerror(errno));
		return;
	}
	if (read(fd, &player, sizeof(player)) != sizeof(player) && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> player\n", ERROR);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use) {
			close(fd);
			return;
		}
	}
	if (read(fd, &game->characterChosed, sizeof(game->characterChosed)) != sizeof(game->characterChosed) && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> sex\n", ERROR);
		close(fd);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use) {
			close(fd);
			return;
		}
	}
	player.movement.animationClock = getPlayer(game->characters.content, game->characters.length)->movement.animationClock;
	player.movement.stateClock = getPlayer(game->characters.content, game->characters.length)->movement.stateClock;
	player.stats.energyRegenClock = getPlayer(game->characters.content, game->characters.length)->stats.energyRegenClock;
	for (int j = 0; j < DAMAGES_TYPE_NB; j++)
		player.damageClock[j] = getPlayer(game->characters.content, game->characters.length)->damageClock[j];
	free(game->map);
	free(game->bg);
	free(game->loadedMap);
	game->map = NULL;
	if (read(fd, &len, sizeof(len)) != sizeof(len) && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> len\n", ERROR);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use)
			return;
	} else if ((game->loadedMap = malloc(len + 1)) == NULL) {
		printf("%s: Couldn't allocate %iB\n", FATAL, len + 1);
		exit(EXIT_FAILURE);
	} else if (read(fd, game->loadedMap, len) != len && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> map\n", ERROR);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use)
			return;
	} else {
		game->loadedMap[len] = 0;
		buffer = concat(game->loadedMap, ".sav", false, false);
		if (stat(buffer, &st) != -1)
			game->map = loadLevel(buffer, &game->bg);
		else if (stat(game->loadedMap, &st) != -1)
			game->map = loadLevel(game->loadedMap, &game->bg);
		else if (!use) {
			printf("%s: Corrupted save file detected: Saved map not found\n", ERROR);
			use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
			if (!use) {
				close(fd);
				return;
			}
		}
		if (!game->map && !use) {
			printf("%s: Corrupted save file detected: Saved map has invalid data\n", ERROR);
			use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
			if (!use) {
				close(fd);
				return;
			}
		}
		free(buffer);
	}
	close(fd);
	*getPlayer(game->characters.content, game->characters.length) = player;
	printf("%s: Done\n", INFO);
}
