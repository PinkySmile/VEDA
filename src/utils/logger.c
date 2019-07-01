//
// Created by Gegel85 on 01/07/2019.
//

#include <logger.h>

enum LogLevel _currentLogLevel = LOGGER_INFO;
FILE *_logFile = NULL;

bool startLogger(const char *file, enum LogLevel level)
{
	_currentLogLevel = level;
	if (file) {
		if (_logFile)
			fclose(_logFile);
		_logFile = fopen(file, "w");
		if (!_logFile)
			return false;
	}
	return true;
}
