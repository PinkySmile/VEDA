#include "structs.h"
#include "macros.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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

Settings	loadSettings()
{
	Settings	settings;
	int		fd = -1;
	FILE		*stream;

	printf("%s: Loading settings\n", INFO_BEG);
	stream = fopen("save/settings.dat", "rb");
	memset(&settings, 0, sizeof(settings));
	if (stream)
		fd = fileno(stream);
	for (int i = 0; i < NB_OF_KEYS; i++)
		settings.keys[i] = DEFAULT_KEYS[i];
	settings.sfxVolume = 100;
	settings.musicVolume = 100;
	settings.windowSize.x = 640;
	settings.windowSize.y = 480;
	strcpy(settings.lang_id, "en");
	if (fd < 0 || read(fd, &settings, sizeof(settings)) <= 0)
		printf("%s: Couldn't load settings (save/settings.dat: %s)\n", ERROR_BEG, fd < 0 ? strerror(errno) : "Empty file found");
	if (stream)
		fclose(stream);
	return (settings);
}
