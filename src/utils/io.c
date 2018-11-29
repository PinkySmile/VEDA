#include <unistd.h>
#include "io_utils.h"

int	writeByte(int fd, char byte)
{
	return write(fd, &byte, 1);
}

int	writeLongInt(int fd, size_t value)
{
	int	written = 0;

	for (int i = 0; i < sizeof(value); i++) {
		written += writeByte(fd, value % 256);
		value <<= 8;
	}
	return written;
}

int	writeBuffer(int fd, void *buffer, size_t size)
{
	return write(fd, buffer, size);
}

int	writeString(int fd, char *str)
{
	int	written = 0;
	size_t	len = strlen(str);

	written = writeLongInt(fd, len);
	written += writeBuffer(fd, str, len);
	return written;
}
