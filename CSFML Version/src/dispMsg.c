#ifdef __MINGW32__
#	include <windows.h>
#endif

int	dispMsg(char *title, char *content, int variate)
{
	#ifdef __MINGW32__
		return (MessageBox(NULL, content, title, variate));
	#else
		(void)title;
		(void)content;
		(void)variate;
		return (-1);
	#endif
}