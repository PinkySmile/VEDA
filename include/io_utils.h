#ifndef VEDA_IO_UTILS_H
#define VEDA_IO_UTILS_H

#include <stdlib.h>

ssize_t	writeByte(int fd, unsigned char byte);
ssize_t	writeString(int fd, char *str);
ssize_t	writeBuffer(int fd, void *buffer, size_t size);
ssize_t	writeLongInt(int fd, size_t value);
ssize_t	writeVarInt(int fd, size_t value);
ssize_t	writeFloat(int fd, double value);

unsigned char	readByte(int fd);
size_t		readLongInt(int fd);
size_t		readVarInt(int fd);
void		*readBuffer(int fd, void *buffer, size_t size);
char		*readString(int fd);
double		readFloat(int fd);

#endif //VEDA_IO_UTILS_H
