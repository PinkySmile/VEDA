#include "structs.h"
#include "macros.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void		saveSettings(game_t *game)
{
	int		fd;
	struct stat	st;

	printf("%s: Saving settings\n", INFO);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO);
		#ifdef __MINGW32__
			mkdir("save");
		#else
			mkdir("save", 0766);
		#endif
	}
	fd = open("save/settings.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		printf("%s: Couldn't save settings (save/settings.dat: %s)\n", ERROR, strerror(errno));
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
	fd = open("save/settings.dat", O_RDONLY);
	memset(&settings, 0, sizeof(settings));
	if (fd < 0) {
		printf("%s: Couldn't load settings (save/settings.dat: %s)\n", ERROR, strerror(errno));
		memset(&settings.keys, -1, NB_OF_KEYS);
		settings.sfxVolume = 100;
		settings.musicVolume = 100;
		settings.windowSize.x = 640;
		settings.windowSize.y = 480;
		settings.keys[0] = sfKeyZ;
		settings.keys[1] = sfKeyS;
		settings.keys[2] = sfKeyQ;
		settings.keys[3] = sfKeyD;
		settings.keys[4] = sfKeyI;
		settings.keys[5] = sfKeyEscape;
		settings.keys[6] = sfKeyF;
		settings.keys[7] = sfKeyC;
		settings.keys[8] = sfKeyB;
		settings.keys[9] = sfKeyP;
		settings.keys[10] = sfKeyU;
		settings.keys[11] = sfKeyNum1;
		settings.keys[12] = sfKeyNum2;
		settings.keys[13] = sfKeyNum3;
		settings.keys[14] = sfKeyNum4;
		settings.keys[15] = sfKeyNum5;
		settings.keys[16] = sfKeyNum6;
		settings.keys[17] = sfKeyNum7;
		settings.keys[18] = sfKeyNum8;
		settings.keys[19] = sfKeyLShift;
		strcpy(settings.lang_id, "en");
	} else
		read(fd, &settings, sizeof(settings));
	return (settings);
}
