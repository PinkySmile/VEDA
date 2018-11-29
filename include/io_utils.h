#ifndef VEDA_IO_UTILS_H
#define VEDA_IO_UTILS_H

#include <stddef.h>

int	writeByte(int fd, char byte);
int	writeString(int fd, char *str);
int	writeBuffer(int fd, void *buffer, size_t size);
int	writeLongInt(int fd, size_t value);

#endif //VEDA_IO_UTILS_H
