#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "callbacks.h"
#include "configs.h"
#include "buttons_names.h"

const Button_config	button_config[] = {
	{//0
		PLAY,
		{10, 10},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&playButton,
		true
	},
	{//1
		SETTINGS,
		{10, 60},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&settings_button,
		true
	},
	{//2
		QUIT,
		{10, 110},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&quit_button,
		true
	},
	{//3
		SETTINGS,
		{10, 60},
		{150, 40},
		{125, 125, 125, 255},
		{0, 0, 0, 255},
		&settings_button,
		false
	},
	{//4
		OPTIONS,
		{200, 10},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&options_button,
		false
	},
	{//5
		AUDIO,
		{200, 60},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&audio_button,
		false
	},
	{//6
		LANGUAGE,
		{200, 110},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&lang_button,
		false
	},
	{//7
		CONTROLS,
		{200, 160},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&controls_button,
		false
	},
	{//8
		BACK,
		{200, 210},
		{150, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&backOnTitleScreen,
		false
	},
	{//9
		BACK,
		{540, 440},
		{100, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&backOnTitleScreen,
		false
	},
	{//10
		WINDOWED_BUTTON,
		{10, 110},
		{200, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&windowed,
		false
	},
	{//11
		FULLSCREEN_BUTTON,
		{10, 10},
		{200, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&fullScreen,
		false
	},
	{//12
		BORDERLESS_BUTTON,
		{10, 60},
		{200, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&borderless,
		false
	},
	{//13
		DISP_FPS,
		{10, 160},
		{200, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&FPS_button,
		false
	},
	{//14
		CONFIRM,
		{0, 440},
		{125, 40},
		{205, 205, 205, 255},
		{0, 0, 0, 255},
		&changePlayerName,
		false
	},
	{//15
		APPLY,
		{440, 172},
		{125, 40},
		{205, 205, 205, 255},
		{255, 255, 255, 255},
		&applyNewWindowSize,
		false
	},
	{//NULL terminator
		-1,
		{0, 0},
		{0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 255},
		NULL,
		false
	}
};
