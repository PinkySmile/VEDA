NAME =	build/VEDA

ifeq ($(OS),Windows_NT)
	RULE = -G "MinGW Makefiles"
endif

all: $(NAME)

$(NAME):
	mkdir build && cd build && cmake .. $(RULE) && make

clean:
	make -C build clean

fclean:
	$(RM) -r build