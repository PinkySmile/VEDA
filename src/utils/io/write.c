#include <unistd.h>
#include <string.h>
#include "io_utils.h"

ssize_t	writeByte(int fd, char byte)
{
	return write(fd, &byte, 1);
}

ssize_t	writeLongInt(int fd, size_t value)
{
	int	written = 0;

	for (int i = 0; i < sizeof(value); i++) {
		written += writeByte(fd, value % 256);
		value >>= 8;
	}
	return written;
}

ssize_t writeVarInt(int fd, size_t value)
{
	int written = 0;
	char byte = 0;

	for (int i = 0; !i || value; i++) {
		byte = value % 128;
		if (value >= 128)
			byte += 128;
		written += write(fd, &byte, 1);
		value >>= 7;
	}
	return written;
}

ssize_t	writeBuffer(int fd, void *buffer, size_t size)
{
	return write(fd, buffer, size);
}

ssize_t	writeString(int fd, char *str)
{
	ssize_t	written = 0;
	size_t	len = strlen(str);

	written = writeVarInt(fd, len);
	written += writeBuffer(fd, str, len);
	return written;
}
