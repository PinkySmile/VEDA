NAME =	VEDA

SRC = 	main.c			\
	initGame.c		\
	loadSprites.c		\
	loadSounds.c		\
	launchGame.c		\
	manageEvents.c		\
	mainMenu.c		\
	drawSprite.c		\
	settingsMgr.c		\
	load_buttons.c		\
	callbacks.c		\
	int_to_str.c		\
	loadFonts.c		\
	get_nbrlen.c		\
	loadLanguages.c		\
	clic_button.c		\
	loadLevel.c		\
	inGame.c		\
	settings.c		\
	saveFileMgr.c		\
	dispMsg.c		\
	change_buffer.c		\
	battle.c		\
	battleAPI.c		\
	discordRichPresence.c	\
	commands.c		\

OBJ =	$(SRC:%.c=src/%.o)

INC =	-Iinclude			\
	-Ilib/concatf/include		\
	-Ilib/configParser/include	\

CSFML = -lcsfml-audio		\
	-lcsfml-graphics	\
	-lcsfml-network		\
	-lcsfml-system		\
	-lcsfml-window		\


LDFLAGS =			\
	-L lib/configParser	\
	-L lib/concatf		\
	-lm			\
	-lconcatf		\
	-lconfigParser		\
	-llua			\
	-ldiscord-rpc		\
	-lpthread		\

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
	g++ -o $(NAME) $(OBJ) $(LDFLAGS) $(CSFML) $(RES) 

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

epi:	CSFML = -lc_graph_prog
epi:	CFLAGS += -g -O0
epi:	RULE = dbg
epi:	re
