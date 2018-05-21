NAME =	levelConverter

SRC = 	levelConverter.c	\
	../../src/concat.c	\

OBJ =	$(SRC:%.c=%.o)

INC =	-I../../include			\
	-I../../lib/concatf/include	\

CFLAGS= $(INC) \
	-W \
	-Wall \
	-Wextra \

CC =	gcc

LDFLAGS =	-L ../../lib/concatf	\
		-lconcatf		\

all:    $(NAME)

$(NAME):$(OBJ)
	$(MAKE) -C ../../lib/concatf
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) -C ../../lib/concatf clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C ../../lib/concatf fclean
	$(RM) $(NAME) $(NAME).exe

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re


