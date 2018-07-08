NAME =	VEDA

SRC = 	main.c		\
	initGame.c	\
	loadSprites.c	\
	loadSounds.c	\
	launchGame.c	\
	manageEvents.c	\
	mainMenu.c	\
	drawSprite.c	\
	settingsMgr.c	\
	load_buttons.c	\
	callbacks.c	\
	int_to_str.c	\
	loadFonts.c	\
	get_nbrlen.c	\
	loadLanguages.c	\
	clic_button.c	\
	loadLevel.c	\
	inGame.c	\
	settings.c	\
	saveFileMgr.c	\
	dispMsg.c	\
	change_buffer.c	\
	battle.c	\
	battleAPI.c	\

OBJ =	$(SRC:%.c=src/%.o)

INC =	-Iinclude			\
	-Ilib/concatf/include		\
	-Ilib/configParser/include	\

LDFLAGS =			\
	-L lib/configParser	\
	-L lib/concatf		\
	-lcsfml-audio		\
	-lcsfml-graphics	\
	-lcsfml-network		\
	-lcsfml-system		\
	-lcsfml-window		\
	-lm			\
	-lconcatf		\
	-lconfigParser		\
	-llua			\

CFLAGS= $(INC)		\
	-W		\
	-Wall		\
	-Wextra		\
	-Wno-parentheses\

CC =	gcc

RULE =	all

LIBS =	lib/configParser/libconfigParser.a	\
	lib/concatf/libconcatf.a		\

RES =	

all:	$(LIBS) $(NAME)

windows:RES = icon.res
windows:icon.res all

icon.res:
	windres icon.rc -O coff -o icon.res

lib/configParser/libconfigParser.a:
	$(MAKE) -C lib/configParser $(RULE)

lib/concatf/libconcatf.a:
	$(MAKE) -C lib/concatf $(RULE)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(RES)

clean:
	$(MAKE) -C lib/concatf clean
	$(MAKE) -C lib/configParser clean
	$(RM) $(OBJ)
	$(RM) icon.res

fclean:	clean
	$(RM) $(NAME) $(NAME).exe

ffclean:fclean
	$(MAKE) -C lib/concatf fclean
	$(MAKE) -C lib/configParser fclean

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	RULE = dbg
dbg:	ffclean all

epi:	LDFLAGS = -lc_graph_prog -lm -lconcatf -L lib/concatf -L lib/configParser -lconfigParser
epi:	CFLAGS += -g -O0
epi:	RULE = dbg
epi:	re
