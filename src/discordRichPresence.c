#include <discord_rpc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

void	initDiscordRichPresence(void)
{
	DiscordEventHandlers	handlers;

	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize("467352301506658304", &handlers, 1, NULL);
}

void	updateDiscordPresence(char *details, char *state, int timestamp, bool end, char *large_image, char *small_image, char *large_text, char *small_text)
{
	DiscordRichPresence	discordPresence;

	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = state;
	discordPresence.details = details;
	if (end)
		discordPresence.endTimestamp = timestamp;
	else
		discordPresence.startTimestamp = timestamp;
	discordPresence.largeImageKey = large_image;
	discordPresence.largeImageText = large_text;
	discordPresence.smallImageKey = small_image;
	discordPresence.smallImageText = small_text;
	Discord_UpdatePresence(&discordPresence);
}