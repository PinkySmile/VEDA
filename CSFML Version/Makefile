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

OBJ =	$(SRC:%.c=src/%.o)

INC =	-Iinclude

LDFLAGS =			\
	-lcsfml-audio		\
	-lcsfml-graphics	\
	-lcsfml-network		\
	-lcsfml-system		\
	-lcsfml-window		\
	-lm

CFLAGS= $(INC) \
	-W \
	-Wall \
	-Wextra \

CC =	gcc

all:    $(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME) $(NAME).exe

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re

epi:	LDFLAGS = -lc_graph_prog -lm
epi:	re
