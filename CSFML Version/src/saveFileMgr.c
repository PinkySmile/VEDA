#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "structs.h"
#include "macros.h"

bool	saveGame(game_t *game)
{
	int		fd;
	struct stat	st;
	bool		success = false;
	Character	player = ((Character *)game->characters.content)[0];

	printf("%s: Saving game\n", INFO);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO);
		#ifdef __MINGW32__
			success = (mkdir("save") == 0);
		#else
			success = (mkdir("save", 0766) == 0);
		#endif
		if (!success) {
			printf("%s: Counldn't create folder \"save\"\n", ERROR);
			return (false);
		}
	}
	fd = open("save/game.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR, strerror(errno));
		return (false);
	}
	player.movement.animationClock = NULL;
	player.movement.stateClock = NULL;
	player.stats.energyRegenClock = NULL;
	write(fd, &player, sizeof(player));
	close(fd);
	return (true);
}

void	loadGame(game_t *game)
{
	int		fd;
	Character	player;

	printf("%s: Loading game\n", INFO);
	fd = open("save/game.dat", O_RDONLY);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR, strerror(errno));
		return;
	}
	read(fd, &player, sizeof(player));
	player.movement.animationClock = ((Character *)game->characters.content)[0].movement.animationClock;
	player.movement.stateClock = ((Character *)game->characters.content)[0].movement.stateClock;
	player.stats.energyRegenClock = ((Character *)game->characters.content)[0].stats.energyRegenClock;
	for (int j = 0; j < DAMAGES_TYPE_NB; j++)
		player.damageClock[j] = ((Character *)game->characters.content)[0].damageClock[j];
	((Character *)game->characters.content)[0] = player;
	close(fd);
}
