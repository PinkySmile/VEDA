NAME =	VEDA

SRC =										\
	main.c									\
	objects_creater.c						\
											\
	battle/base_functions.c					\
	battle/characters.c						\
	battle/lib.c							\
	battle/projectiles.c					\
											\
	buttons_callbacks/change_window_mode.c	\
	buttons_callbacks/menus.c				\
	buttons_callbacks/options_buttons.c		\
	buttons_callbacks/settings_menus.c		\
											\
	character/deal_damages.c				\
	character/move.c						\
	character/exec_action.c					\
											\
	config_loader/save_file_mgr/save.c		\
	config_loader/save_file_mgr/load.c		\
	config_loader/settings_mgr.c			\
											\
	configs/buttons.c						\
	configs/fonts.c							\
	configs/menus.c							\
	configs/sounds.c						\
	configs/sprites.c						\
											\
	core/globals.c							\
	core/launch_game.c						\
	core/sighandlers.c						\
											\
	destroyers/destroy_battle.c				\
	destroyers/destroy_buttons.c			\
	destroyers/destroy_characters.c			\
	destroyers/destroy_dialogs.c			\
	destroyers/destroy_fonts.c				\
	destroyers/destroy_languages.c			\
	destroyers/destroy_ressources.c			\
	destroyers/destroy_sfml_objects.c		\
	destroyers/destroy_sounds.c				\
	destroyers/destroy_sprites.c			\
											\
	dialogs/commands.c						\
	dialogs/create_dialog.c					\
	dialogs/display_dialogs.c				\
											\
	display_map/display_characters.c		\
	display_map/display_terrain.c			\
											\
	events/event_closed.c					\
	events/event_joystick_button_pressed.c	\
	events/event_joystick_moved.c			\
	events/event_key_pressed.c				\
	events/event_mouse_click.c				\
	events/event_mouse_moved.c				\
	events/event_mouse_released.c			\
	events/event_text_entered.c				\
	events/manage_events.c					\
											\
	hud/display_damages.c					\
	hud/draw_hud.c							\
	hud/life_bar.c 							\
	hud/energy_bar.c 						\
											\
	load_ressources/battle.c				\
	load_ressources/buttons.c				\
	load_ressources/context_callbacks.c		\
	load_ressources/fonts.c					\
	load_ressources/init_game.c				\
	load_ressources/languages.c				\
	load_ressources/level.c					\
	load_ressources/loading_bar.c			\
	load_ressources/projectiles.c			\
	load_ressources/sounds.c				\
	load_ressources/sprites.c				\
											\
	menus/battle.c							\
	menus/change_buffer.c					\
	menus/in_game.c							\
	menus/main_menu.c						\
	menus/settings.c						\
											\
	utils/discord_rich_presence.c			\
	utils/disp_msg.c						\
	utils/display_buttons.c					\
	utils/display_rectangle.c				\
	utils/draw_sprite.c						\
	utils/draw_text.c						\
	utils/is_folder.c						\
	utils/is_key_pressed.c					\
	utils/get_absolute_path.c				\
	utils/get_parent_folder.c				\
	utils/getline.c							\
	utils/get_player.c						\
	utils/get_text_size.c					\
	utils/play_sound_effect.c				\
	utils/split.c							\
	utils/transform_key_to_string.c			\
	utils/unicode_mgr.c						\
											\
	utils/io/read.c							\
	utils/io/write.c						\

OBJ =	$(SRC:%.c=src/%.o)

INC =	-Iinclude				\
	-Ilib/concatf/include		\
	-Ilib/configParser/include	\

CSFML = -lcsfml-audio		\
		-lcsfml-graphics	\
		-lcsfml-network		\
		-lcsfml-system		\
		-lcsfml-window		\


LDFLAGS =				\
	-L lib/configParser	\
	-L lib/concatf		\
	-lm					\
	-lconcatf			\
	-lconfigParser		\
	-llua				\
	-ldiscord-rpc		\
	-lpthread			\

CFLAGS= $(INC)	\
		-W		\
		-Wall	\
		-Wextra	\

CC =	gcc

RULE =	all

LIBS =	lib/configParser/libconfigParser.a	\
		lib/concatf/libconcatf.a			\

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
