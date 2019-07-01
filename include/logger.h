//
// Created by Gegel85 on 01/07/2019.
//

#ifndef VEDA_LOGGER_H
#define VEDA_LOGGER_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LOGGER_INFO_BEGIN	"[INFO]:   "
#define LOGGER_ERROR_BEGIN	"[ERROR]:  "
#define LOGGER_DEBUG_BEGIN	"[DEBUG]:  "
#define LOGGER_FATAL_BEGIN	"[FATAL]:  "
#define LOGGER_WARNING_BEGIN	"[WARNING]:"
#define LOGGER_UNKNOWN_BEGIN	"[???]:    "

enum LogLevel {
	LOGGER_NO_LOGGING,
	LOGGER_FATAL,
	LOGGER_ERROR,
	LOGGER_WARNING,
	LOGGER_INFO,
	LOGGER_DEBUG
};

extern enum LogLevel _currentLogLevel;
extern FILE *_logFile;

#define logMsg(logLevel, message, ...) do { \
	if (logLevel > _currentLogLevel)\
		break;\
	\
	time_t __timestamp = time(NULL);\
	struct tm *__tm = localtime(&__timestamp);\
	char __buffer[300];\
	\
	strftime(__buffer, sizeof(__buffer), "[%d-%m-%Y][%H:%M:%S]", __tm);\
	switch (logLevel) {\
	case LOGGER_FATAL:\
		strcat(__buffer, LOGGER_FATAL_BEGIN);\
		break;\
	case LOGGER_ERROR:\
		strcat(__buffer, LOGGER_ERROR_BEGIN);\
		break;\
	case LOGGER_WARNING:\
		strcat(__buffer, LOGGER_WARNING_BEGIN);\
		break;\
	case LOGGER_INFO:\
		strcat(__buffer, LOGGER_INFO_BEGIN);\
		break;\
	case LOGGER_DEBUG:\
		strcat(__buffer, LOGGER_DEBUG_BEGIN);\
		break;\
	default:\
		strcat(__buffer, LOGGER_UNKNOWN_BEGIN);\
	}\
	fprintf(stderr, "%s ", __buffer);\
	fprintf(stderr, message, ##__VA_ARGS__);\
	fprintf(stderr, "\n");\
	if (_logFile) {\
		fprintf(_logFile, "%s ", __buffer);\
		fprintf(_logFile, message, ##__VA_ARGS__);\
		fprintf(_logFile, "\n");\
        }\
} while (0)

bool startLogger(const char *file, enum LogLevel);

#endif //VEDA_LOGGER_H
