#include <unistd.h>
#include <string.h>
#include <creators.h>
#include "io_utils.h"

unsigned char	readByte(int fd)
{
	unsigned char	byte;

	read(fd, &byte, 1);
	return byte;
}

size_t	readLongInt(int fd)
{
	size_t	value = 0;

	for (int i = 0; i < 8; i++)
		value += readByte(fd) << i * 8;
	return value;
}

size_t	readVarInt(int fd)
{
	size_t	value = 0;
	char	byte = 0;
	int	i = 0;

	do {
		byte = readByte(fd);
		value += byte << 7 * i++;
	} while (byte & 128);
	return value;
}

double	readFloat(int fd)
{
	size_t	value = readLongInt(fd);

	return *(double *)&value;
}

void	*readBuffer(int fd, void *buffer, size_t size)
{
	if (!buffer)
		buffer = protectedMalloc(size);
	read(fd, buffer, size);
	return buffer;
}

char	*readString(int fd)
{
	size_t	len = readVarInt(fd);
	char	*buffer = protectedMalloc(len + 1);

	readBuffer(fd, buffer, len);
	buffer[len] = '\0';
	return buffer;
}
