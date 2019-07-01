#if defined _WIN32
#	include <windows.h>
#endif
#include <logger.h>
#include <signal.h>
#include <functions.h>
#include <discord_rpc.h>
#include <destructors.h>
#include <loading.h>
#include <utils.h>

char	*programPath = NULL;

void	setSignalHandler()
{
	signal(2, &sighandler);
	signal(3, &sighandler);
	signal(4, &sighandler);
	signal(6, &sighandler);
	signal(7, &sighandler);
	signal(8, &sighandler);
	signal(11,&sighandler);
	signal(15,&sighandler);
}

void	prepareExit()
{
	destroyStruct();
	Discord_Shutdown();
	free(programPath);
	logMsg(LOGGER_INFO, "Goodbye !");
}

int	main(int argc, char **args)
{
	setSignalHandler();
	programPath = getParentFolder(args[0]);
	initGame(argc == 2 && !strcmp("debug", args[1]));
	launchGame();
	prepareExit();
	return (EXIT_SUCCESS);
}
