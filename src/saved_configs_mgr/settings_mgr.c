#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io_utils.h>
#include "structs.h"
#include "macros.h"
#include "utils.h"

void	saveSettingsToFd(int fd)
{
	writeByte(fd, SAVED_SETTINGS_HEADER);
	writeByte(fd, game.settings.musicVolume);
	writeByte(fd, game.settings.sfxVolume);
	writeByte(fd, game.settings.windowMode);
	writeLongInt(fd, game.settings.windowSize.x);
	writeLongInt(fd, game.settings.windowSize.y);
	writeBuffer(fd, game.settings.keys, sizeof(game.settings.keys));
	writeBuffer(fd, game.settings.lang_id, sizeof(game.settings.lang_id));
	writeBuffer(fd, game.settings.playerName, sizeof(game.settings.playerName));
	writeByte(fd, game.settings.dispFramerate);
	writeByte(fd, game.settings.characterChosed);
}

void	saveSettingsToFile(char *path)
{
	int	fd = -1;
	FILE	*stream;

	stream = fopen(path, "w+b");
	if (stream)
		fd = fileno(stream);
	if (fd < 0) {
		printf("%s: Couldn't save settings (%s: %s)\n", ERROR_BEG, path, strerror(errno));
		if (stream)
			fclose(stream);
	} else {
		saveSettingsToFd(fd);
		fclose(stream);
	}
}

void	saveSettings()
{
	struct stat	st;

	printf("%s: Saving settings\n", INFO_BEG);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO_BEG);
		#ifdef __MINGW32__
			mkdir("save");
		#else
			mkdir("save", 0766);
		#endif
	}

	saveSettingsToFile("save/settings.dat");
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

void	readSettingsV1(int fd, Settings *settings)
{
	settings->musicVolume = readByte(fd);
	settings->sfxVolume = readByte(fd);
	settings->windowMode = readByte(fd);
	settings->windowSize.x = readLongInt(fd);
	settings->windowSize.y = readLongInt(fd);
	readBuffer(fd, settings->keys, sizeof(settings->keys));
	readBuffer(fd, settings->lang_id, sizeof(settings->lang_id));
	readBuffer(fd, settings->playerName, sizeof(settings->playerName));
	settings->dispFramerate = readByte(fd);
	settings->characterChosed = readByte(fd);
}

Settings	loadSettingsFromFd(int fd)
{
	Settings	settings;
	char		version = readByte(fd);

	if (version <= 100) {
		printf("%s: Settings are saved with an old format. This might cause some issues.\n", WARNING_BEG);
		read(fd, &settings, sizeof(settings));
	} else if (version == 101) {
		printf("%s: Settings file version is up to date\n", INFO_BEG);
		readSettingsV1(fd, &settings);
	} else {
		printf("%s: Settings file version is invalid (%u)\n", ERROR_BEG, version);
		return getDefaultSettings();
	}
	return settings;
}

Settings	loadSettingsFromFile(char *path)
{
	Settings	settings;
	int		fd = -1;
	FILE		*stream;

	stream = fopen(path, "rb");
	if (stream)
		fd = fileno(stream);
	if (fd < 0) {
		printf(
			"%s: Couldn't load settings (%s: %s)\n",
			ERROR_BEG,
			path,
			strerror(errno)
		);
		settings = getDefaultSettings();
	} else
		settings = loadSettingsFromFd(fd);
	if (stream)
		fclose(stream);
	return settings;
}

Settings	loadSettings()
{
	Settings	settings;
	sfVideoMode	mode = sfVideoMode_getDesktopMode();

	printf("%s: Loading settings\n", INFO_BEG);
	settings = loadSettingsFromFile("save/settings.dat");
	if (game.settings.windowMode == FULLSCREEN || game.settings.windowMode == BORDERLESS_WINDOW) {
		settings.windowSize.x = mode.width;
		settings.windowSize.y = mode.height;
	} else {
		if (settings.windowSize.x > mode.width)
			settings.windowSize.x = mode.width;
		if (settings.windowSize.y > mode.height)
			settings.windowSize.y = mode.height;
		if (!getLanguage(findLanguage(settings.lang_id)))
			strcpy(settings.lang_id, "en");
	}
	settings.dispFramerate = true;
	return (settings);
}
