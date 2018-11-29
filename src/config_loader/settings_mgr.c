#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "structs.h"
#include "macros.h"
#include "utils.h"

void	saveSettings()
{
	int		fd = -1;
	struct stat	st;
	FILE		*stream;

	printf("%s: Saving settings\n", INFO_BEG);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO_BEG);
		#ifdef __MINGW32__
			mkdir("save");
		#else
			mkdir("save", 0766);
		#endif
	}
	stream = fopen("save/settings.dat", "w+b");
	if (stream)
		fd = fileno(stream);
	if (fd < 0) {
		printf("%s: Couldn't save settings (save/settings.dat: %s)\n", ERROR_BEG, strerror(errno));
		return;
	}
	write(fd, &game.settings, sizeof(game.settings));
	close(fd);
}

Settings	getDefaultSettings()
{
	Settings	settings;

	memset(&settings, 0, sizeof(settings));
	for (int i = 0; i < NB_OF_KEYS; i++)
		settings.keys[i] = DEFAULT_KEYS[i];
	settings.sfxVolume = 100;
	settings.musicVolume = 100;
	settings.windowSize.x = 640;
	settings.windowSize.y = 480;
	strcpy(settings.lang_id, "en");
	return settings;
}

Settings	loadSettings()
{
	Settings	settings;
	int		fd = -1;
	FILE		*stream;
	sfVideoMode	mode = sfVideoMode_getDesktopMode();
	ssize_t		readBytes = 0;

	printf("%s: Loading settings\n", INFO_BEG);
	stream = fopen("save/settings.dat", "rb");
	if (stream)
		fd = fileno(stream);
	readBytes = read(fd, &settings, sizeof(settings));
	if (fd < 0) {
		printf(
			"%s: Couldn't load settings (save/settings.dat: %s)\n",
			ERROR_BEG,
			strerror(errno)
		);
		settings = getDefaultSettings();
	}
	if (readBytes <= 0) {
		printf(
			"%s: Couldn't load settings (save/settings.dat: Empty file found)\n",
			ERROR_BEG
		);
		settings = getDefaultSettings();
	}
	if (stream)
		fclose(stream);
	if (game.settings.windowMode == FULLSCREEN || game.settings.windowMode == BORDERLESS_WINDOW) {
		settings.windowSize.x = mode.width;
		settings.windowSize.y = mode.height;
	} else {
		if (settings.windowSize.x > mode.width)
			settings.windowSize.x = mode.width;
		if (settings.windowSize.y > mode.height - 60)
			settings.windowSize.y = mode.height - 60;
		if (!getLanguage(findLanguage(settings.lang_id)))
			strcpy(settings.lang_id, "en");
	}
	settings.dispFramerate = true;
	return (settings);
}
