#include <stdlib.h>

#if defined _WIN32 || defined __WIN32 || defined __WIN32__

long	random()
{
	return rand();
}

void	srandom(long seed)
{
	srand(seed);
}

#endif