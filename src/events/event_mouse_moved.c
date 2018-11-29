#include <structs.h>
#include <utils.h>
#include <stdlib.h>

void	manageMouseMoved(sfEvent *event)
{
	if (game.state.menuSelected == 1 && game.state.menu == 3) {
		if (event->mouseMove.x <= 140 * game.settings.baseScale.x)
			game.settings.sfxVolume = 0;
		else if (event->mouseMove.x >= 440 * game.settings.baseScale.x)
			game.settings.sfxVolume = 100;
		else
			game.settings.sfxVolume = (event->mouseMove.x / game.settings.baseScale.x - 140) / 3;
		if (getSoundEffect(DIRT1 + random() % 4))
			playSoundEffect(getSoundEffect(DIRT1 + random() % 4));

	} else if (game.state.menuSelected == 2 && game.state.menu == 3) {
		if (event->mouseMove.x <= 140 * game.settings.baseScale.x)
			game.settings.musicVolume = 0;
		else if (event->mouseMove.x >= 440 * game.settings.baseScale.x)
			game.settings.musicVolume = 100;
		else
			game.settings.musicVolume = (event->mouseMove.x / game.settings.baseScale.x - 140) / 3;
		setVolumes(game.resources.musics, game.settings.musicVolume);

	} else if (game.state.menuSelected == 1 && game.state.menu == 4) {
		if (event->mouseMove.x <= 272 * game.settings.baseScale.x)
			game.newSize.x = 256;
		else if (event->mouseMove.x >= 572 * game.settings.baseScale.x)
			game.newSize.x = game.state.currentDesktopMode.width;
		else
			game.newSize.x = (event->mouseMove.x / game.settings.baseScale.x - 272) * (game.state.currentDesktopMode.width - 256) / 300 + 256;

	} else if (game.state.menuSelected == 2 && game.state.menu == 4) {
		if (event->mouseMove.x <= 272 * game.settings.baseScale.x)
			game.newSize.y = 144;
		else if (event->mouseMove.x >= 572 * game.settings.baseScale.x)
			game.newSize.y = game.state.currentDesktopMode.height;
		else
			game.newSize.y = (event->mouseMove.x / game.settings.baseScale.x - 272) * (game.state.currentDesktopMode.height - 144) / 300 + 144;
	}
}