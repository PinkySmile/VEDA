NAME =	VEDA

SRC = 	main.c		\
	initGame.c	\
	concat.c	\
	loadMusics.c	\
	loadSprites.c	\
	loadSfx.c	\
	launchGame.c	\
	manageEvents.c	\

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
	$(RM) $(NAME)
	$(RM) score.dat

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re