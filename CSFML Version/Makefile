NAME =	VEDA

SRC = 	main.c		\
	initGame.c	\
	concat.c	\
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

OBJ =	$(SRC:%.c=src/%.o)

INC =	-Iinclude		\
	-Ilib/concatf/include	\

LDFLAGS =			\
	-lcsfml-audio		\
	-lcsfml-graphics	\
	-lcsfml-network		\
	-lcsfml-system		\
	-lcsfml-window		\
	-lm			\
	-lconcatf		\
	-L lib/concatf		\

CFLAGS= $(INC) \
	-W \
	-Wall \
	-Wextra \

CC =	gcc

all:    $(NAME)

$(NAME):$(OBJ)
	$(MAKE) -C lib/concatf
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) -C lib/concatf clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C lib/concatf fclean
	$(RM) $(NAME) $(NAME).exe

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re

epi:	LDFLAGS = -lc_graph_prog -lm -lconcatf -L lib/concatf
epi:	dbg
