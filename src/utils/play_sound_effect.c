#include <stdbool.h>
#include <SFML/Audio.h>
#include <malloc.h>
#include <string.h>
#include <structs.h>
#include "creators.h"

int	playSoundEffect(sfSoundBuffer *buffer)
{
	static	sfSound		*sounds[SOUNDS_BUFFER_SIZE];
	static	sfSoundBuffer	*buffers[SOUNDS_BUFFER_SIZE];
	static	bool		first = true;

	if (first) {
		first = false;
		memset(buffers, 0, sizeof(buffers));
		for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++)
			sounds[i] = createSound();
	}
	if (!buffer) {
		for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++)
			sfSound_destroy(sounds[i]);
		return (0);
	}
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) {
		if (!buffers[i]) {
			buffers[i] = buffer;
			sfSound_setBuffer(sounds[i], buffers[i]);
			sfSound_setVolume(sounds[i], game.settings.sfxVolume);
			sfSound_play(sounds[i]);
			return (0);
		} else if(buffers[i] == buffer && sfSound_getStatus(sounds[i]) != sfPlaying) {
			sfSound_setPlayingOffset(sounds[i], (sfTime){0});
			sfSound_setVolume(sounds[i], game.settings.sfxVolume);
			sfSound_play(sounds[i]);
			return (0);
		}
	}
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) {
		if(sfSound_getStatus(sounds[i]) != sfPlaying) {
			sfSound_setBuffer(sounds[i], buffer);
			sfSound_setVolume(sounds[i], game.settings.sfxVolume);
			buffers[i] = buffer;
			sfSound_play(sounds[i]);
			return (0);
		}
	}
	return (2);
}