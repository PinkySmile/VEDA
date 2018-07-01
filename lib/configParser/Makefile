NAME =	libconfigParser.a

FILE =	parser.c	\
	floats.c	\
	ints.c		\
	bools.c		\
	strings.c	\
	dicts.c		\
	data.c		\
	arrays.c	\
	lists.c		\
	dumper.c	\
	debug.c		\

SRC =	$(FILE:%.c=sources/%.o)

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude

CFLAGS=	$(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

CC =	gcc

all:	$(NAME)

$(NAME):$(OBJ)
	$(AR) rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re
