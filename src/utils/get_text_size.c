#include <SFML/Graphics.h>

sfVector2f	getTextSize(const char *str, const sfFont *font, unsigned size)
{
	sfVector2f	result = {0, size};
	float		current = 0;

	for (int i = 0; str[i]; i++) {
		current += sfFont_getGlyph(font, (unsigned char)str[i], size, sfFalse, 1).advance;
		if (current > result.x)
			result.x = current;
		if (str[i] == '\n') {
			result.y += size;
			current = 0;
		} else if (str[i] == '\r')
			current = 0;
		else if (str[i] == '\v')
			result.y += size;
	}
	return result;
}