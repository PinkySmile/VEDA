#include <SFML/Graphics.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

size_t	strlen_unicode(sfUint32 *str)
{
	size_t i = 0;

	for (; str[i]; i++);
	return (i);
}

size_t	calcStringLen(sfUint32 *str)
{
	size_t	len = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] < 0x80)
			len++;
		else if (str[i] < 0x800)
			len += 2;
		else if (str[i] < 0x10000)
			len += 3;
		else
			len += 4;
	}
	return (len);
}

float	getWordSize(sfUint32 *string, int start, int end, sfFont *font, int size)
{
	float	result = 0;

	for (int i = start; string[i] && i < end; i++)
		result += sfFont_getGlyph(font, string[i], size, false, 0).advance;
	return (result);
}

size_t	getWordPosition(sfUint32 *string, float position, sfFont *font, unsigned int size)
{
	float	result = 0;

	for (size_t i = 0; string[i]; i++) {
		if (result >= position)
			return (i);
		result += sfFont_getGlyph(font, string[i], size, false, 0).advance;
	}
	return (strlen_unicode(string));
}

sfUint32	*convertUtf8toUtf32(sfUint8 *str, sfUint32 *buffer)
{
	int	bufferIndex = 0;

	if (!buffer)
		buffer = malloc(strlen(str) * sizeof(*buffer));
	if (!buffer)
		return (NULL);
	for (int i = 0; str[i]; i++)
		if (str[i] >= 240) {
			buffer[bufferIndex++] = (
				(str[i] - 240) << 18
			) + (
				(str[i + 1] - 128) << 12
			) + (
				(str[i + 2] - 128) << 6
			) + str[i + 3] - 128;
			i += 3;
		} else if (str[i] >= 224) {
			buffer[bufferIndex++] = (
				(str[i] - 224) << 12
			) + (
				(str[i + 1] - 128) << 6
			) + str[i + 2] - 128;
			i += 2;
		} else if (str[i] >= 192) {
			buffer[bufferIndex++] = (
				(str[i] - 192) << 6
			) + str[i + 1] - 128;
			i++;
		} else
			buffer[bufferIndex++] = str[i];
	buffer[bufferIndex] = 0;
	return (buffer);
}

sfUint8	*convertUtf32toUtf8(sfUint32 *str, sfUint8 *buffer)
{
	int	bufferIndex = 0;

	if (!buffer)
		buffer = malloc((calcStringLen(str) + 1) * sizeof(*buffer));
	if (!buffer)
		return (NULL);
	for (int i = 0; str[i]; i++)
		if (str[i] < 0x80) {
			buffer[bufferIndex++] = str[i];
		} else if (str[i] < 0x800) {
			buffer[bufferIndex++] = (str[i] >> 6) + 192;
			buffer[bufferIndex++] = str[i] % (1 << 6) + 128;
		} else if (str[i] < 0x10000) {
			buffer[bufferIndex++] = (str[i] >> 12) + 224;
			buffer[bufferIndex++] = (str[i] >> 6) % (1 << 12) + 128;
			buffer[bufferIndex++] = str[i]  % (1 << 6) + 128;
		} else {
			buffer[bufferIndex++] = (str[i] >> 18) + 240;
			buffer[bufferIndex++] = (str[i] >> 12) % (1 << 18) + 128;
			buffer[bufferIndex++] = (str[i] >> 6) % (1 << 12) + 128;
			buffer[bufferIndex++] = str[i] % (1 << 6)+ 128;
		}
	buffer[bufferIndex] = 0;
	return (buffer);
}