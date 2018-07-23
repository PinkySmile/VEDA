#ifndef __DISCORD_RICH_PRESENCE_HEADER_
#define __DISCORD_RICH_PRESENCE_HEADER_

void	initDiscordRichPresence(void);
void	updateDiscordPresence(char *state, char *details, int timestamp, bool end, char *large_image, char *small_image, char *large_text, char *small_text);

#endif