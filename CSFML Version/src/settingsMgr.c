#include "structs.h"
#include "macros.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void		saveSettings(game_t *game)
{
	int	fd;

	printf("%s: Saving settings\n", INFO);
	fd = open("data/settings.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		printf("%s: Couldn't save settings (data/settings.dat: %s)\n", ERROR, strerror(errno));
		return;
	}
	write(fd, &game->settings, sizeof(game->settings));
	close(fd);
}

Settings	loadSettings()
{
	Settings	settings;
	int		fd;

	printf("%s: Loading settings\n", INFO);
	fd = open("data/settings.dat", O_RDONLY);
	memset(&settings, 0, sizeof(settings));
	if (fd < 0) {
		printf("%s: Couldn't save settings (data/settings.dat: %s)\n", ERROR, strerror(errno));
		memset(&settings.keys, -1, NB_OF_KEYS);
		settings.sfxVolume = 100;
		settings.musicVolume = 100;
		settings.windowSize.x = 640;
		settings.windowSize.y = 480;
	} else
		read(fd, &settings, sizeof(settings));
	return (settings);
}
