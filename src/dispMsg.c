#ifdef __MINGW32__
#	include <windows.h>
#else
#	include <SFML/Graphics.h>
#endif
#include "macros.h"

int	dispMsg(char *title, char *content, int variate)
{
	#ifdef __MINGW32__
		return (MessageBox(NULL, content, title, variate));
	#else
		char			**buttons = NULL;
		int			clicked = -1;
		sfRenderWindow		*win;
		sfVideoMode		mode = {700, 220, 32};
		sfEvent			event;
		sfRectangleShape	*rect = sfRectangleShape_create();
		sfFont			*font = sfFont_createFromFile("data/fonts/arial.ttf");
		sfText			*text = sfText_create();
		int			nbOfButtons = 0;
		int			buttonClicked = 0;

		if (!font) {
			printf("%s: Cannot load default font !\nDisplaying the message in the console:\n\n", ERROR);
			printf("%s\n%s\n", title, content);
		}
		switch (variate) {
		case 0:
			buttons = (char *[1]){"OK"};
			nbOfButtons = 1;
			break;
		case 4:
			buttons = (char *[2]){"Yes", "No"};
			nbOfButtons = 2;
			break;
		}
		win = sfRenderWindow_create(mode, title ? title : "null", sfTitlebar | sfClose, NULL);
		if (text && font)
			sfText_setFont(text, font);
		if (!win)
			return (-1);
		if (text)
			sfText_setCharacterSize(text, 15);
		while (sfRenderWindow_isOpen(win)) {
			while (sfRenderWindow_pollEvent(win, &event)) {
				if (event.type == sfEvtClosed)
					sfRenderWindow_close(win);
				if (event.type == sfEvtMouseButtonPressed) {
					if (event.mouseButton.button == sfMouseLeft && event.mouseButton.y >= 150 && event.mouseButton.y <= 170) {
						buttonClicked = (event.mouseButton.x - 400 + 70 * nbOfButtons) / 70;
						if (buttonClicked >= 0 && buttonClicked < nbOfButtons) {
							clicked = nbOfButtons == 2 ? (buttonClicked == 0 ? 6 : 5) : 0;
							sfRenderWindow_close(win);
						}
					}
				}
			}
			sfRenderWindow_clear(win, (sfColor){200, 200, 200, 255});
			if (rect) {
				sfRectangleShape_setFillColor(rect, (sfColor){255, 255, 255, 255});
				sfRectangleShape_setSize(rect, (sfVector2f){60, 20});
			}
			if (text) {
				sfText_setColor(text, (sfColor){0, 0, 0, 255});
				sfText_setPosition(text, (sfVector2f){10, 40});
				sfText_setString(text, content ? content : "null");
				sfRenderWindow_drawText(win, text, NULL);
			}
			for (int i = 0; i < nbOfButtons; i++) {
				if (rect) {
					sfRectangleShape_setPosition(rect, (sfVector2f){400 - 70 * (nbOfButtons - i), 150});
					sfRenderWindow_drawRectangleShape(win, rect, NULL);
				}
				if (text) {
					sfText_setString(text, buttons[i]);
					sfText_setPosition(text, (sfVector2f){410 - 70 * (nbOfButtons - i), 150});
					sfRenderWindow_drawText(win, text, NULL);
				}
			}
			sfRenderWindow_display(win);
		}
		sfRenderWindow_destroy(win);
		sfFont_destroy(font);
		sfText_destroy(text);
		sfRectangleShape_destroy(rect);
		return (clicked);
	#endif
}
