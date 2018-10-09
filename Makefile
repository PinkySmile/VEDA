NAME =	VEDA

SRC =	main.c					\
	objects_creater.c			\
						\
	battle/battle.c				\
	battle/battle_lua/battle_lua.c		\
						\
	buttons_callbacks/callbacks.c		\
						\
	config_loader/save_file_mgr.c		\
	config_loader/settings_mgr.c		\
						\
	configs/buttons.c			\
	configs/fonts.c				\
	configs/menus.c				\
	configs/sounds.c			\
	configs/sprites.c			\
						\
	core/clic_button.c			\
	core/globals.c				\
	core/launch_game.c			\
	core/manage_events.c			\
	core/sighandlers.c			\
						\
	destroyers/destroy_battle.c		\
	destroyers/destroy_buttons.c		\
	destroyers/destroy_characters.c		\
	destroyers/destroy_dialogs.c		\
	destroyers/destroy_fonts.c		\
	destroyers/destroy_languages.c		\
	destroyers/destroy_ressources.c		\
	destroyers/destroy_sfml_objects.c	\
	destroyers/destroy_sounds.c		\
	destroyers/destroy_sprites.c		\
						\
	dialogs/commands.c			\
						\
	hud/draw_hud.c				\
	hud/life_bar.c 				\
	hud/energy_bar.c 			\
						\
	load_ressources/buttons.c		\
	load_ressources/fonts.c			\
	load_ressources/init_game.c		\
	load_ressources/languages.c		\
	load_ressources/level.c			\
	load_ressources/loading_bar.c		\
	load_ressources/sounds.c		\
	load_ressources/sprites.c		\
						\
	menus/battle.c				\
	menus/change_buffer.c			\
	menus/in_game.c				\
	menus/main_menu.c			\
	menus/settings.c			\
						\
	utils/discord_rich_presence.c		\
	utils/disp_msg.c			\
	utils/display_buttons.c			\
	utils/display_rectangle.c		\
	utils/draw_sprite.c			\
	utils/draw_text.c			\
	utils/get_absolute_path.c		\
	utils/get_parent_folder.c		\
	utils/getline.c				\
	utils/transform_key_to_string.c		\

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

CFLAGS= $(INC)			\
	-W			\
	-Wall			\
	-Wextra			\

CC =	gcc

RULE =	all

LIBS =	lib/configParser/libconfigParser.a	\
	lib/concatf/libconcatf.a		\

RES =	

all:	$(LIBS) $(NAME)

windows:RES = icon.res
windows:LDFLAGS += -mwindows
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
