#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <discord_rpc.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "loading.h"
#include "functions.h"
#include "destructors.h"
#if defined _WIN32 || defined __WIN32 || defined __WIN32__
#	include <windows.h>
#endif

char	*programPath = NULL;

#if defined _WIN32 || defined __WIN32 || defined __WIN32__

void	setSignalHandler() {
	signal(SIGINT,  &sighandler);
	signal(SIGILL,  &sighandler);
	signal(SIGABRT, &sighandler);
	signal(SIGFPE,  &sighandler);
	signal(SIGSEGV, &sighandler);
	signal(SIGTERM, &sighandler);
}

#else

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

#endif

void	closeConsole(bool debug) {
#if defined _WIN32 || defined __WIN32 || defined __WIN32__

	if (!debug && !FreeConsole()) //Not in debug: close the console
		printf("%s: Cannot close main console\n", ERROR_BEG);
	else if (debug) {
		AllocConsole(); //In debug: Create a new console
		freopen("CONOUT$", "w", stdout); //Redirect stdout to the console
	} else
		freopen("last.log", "w", stdout);//Redirect stdout to 'last.log'

#else
	(void)debug;
#endif
}

void	prepareExit() {
	destroyStruct();
	Discord_Shutdown();
	free(programPath);
	printf("%s: Goodbye !\n", INFO_BEG);
}

int	main(int argc, char **args) {
	bool debug = (argc == 2 && !strcmp("debug", args[1]));

	debug = true;
	closeConsole(debug);
	setSignalHandler();
	programPath = getParentFolder(args[0]);
	initGame(debug);
	launchGame();
	prepareExit();
	return (EXIT_SUCCESS);
}
