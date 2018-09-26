#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "utils.h"
#include "macros.h"
#include "discord_rp.h"

char	*programPath = NULL;

#if defined _WIN32 || defined __WIN32 || defined __WIN32__

#define SIGQUIT 3
#define SIGBUS 7

#endif

void	setSignalHandler()
{
	signal(SIGINT,  &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGILL,  &sighandler);
	signal(SIGABRT, &sighandler);
	signal(SIGBUS,  &sighandler);
	signal(SIGFPE,  &sighandler);
	signal(SIGSEGV, &sighandler);
	signal(SIGPIPE, &sighandler);
	signal(SIGTERM, &sighandler);
}

void	closeConsole(bool debug)
{
	#if defined _WIN32 || defined __WIN32 || defined __WIN32__
	#include <windows.h>

	if (!debug && !FreeConsole())
		printf("%s: Cannot close main console\n", ERROR);
	#else
	(void)debug;
	#endif
}

void	prepareExit()
{
	destroyStruct();
	Discord_Shutdown();
	free(programPath);
	printf("%s: Goodbye !\n", INFO);
}

int	main(int argc, char **args)
{
	bool	debug = (argc == 2 && !strcmp("debug", args[1]));

	closeConsole(debug);
	setSignalHandler();
	programPath = getProgramPath(args[0]);
	initGame(debug);
	launchGame();
	prepareExit();
	return (EXIT_SUCCESS);
}
