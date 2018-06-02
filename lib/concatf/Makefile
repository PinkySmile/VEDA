NAME =	libconcatf.a

FILE =	my_strlen_rec.c			\
	concatf.c			\
	concat.c			\
	float_to_str.c			\
	my_putnbr_base.c		\
	my_putbase.c			\
	str.c				\
	my_showstr.c			\
	my_compute_power_rec_long.c	\
	my_putstar.c			\
	uint_to_str.c			\
	int_to_str.c			\
	get_nbrlen.c			\
	sub_strings.c			\

SRC =	$(FILE:%.c=sources/%.o)

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude

CFLAGS=	$(INC)

CC =	gcc

all: $(NAME)

$(NAME):$(OBJ)
	$(AR) rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re