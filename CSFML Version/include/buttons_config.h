#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"
#include "buttons_names.h"

const Button_config	button_config[] = {
	{
		PLAY,
		{10, 10},
		{150, 40},
		{205, 205, 205, 255},
		&play_button,
		true
	},
	{
		SETTINGS,
		{10, 60},
		{150, 40},
		{205, 205, 205, 255},
		&settings_button,
		true
	},
	{
		QUIT,
		{10, 110},
		{150, 40},
		{205, 205, 205, 255},
		&quit_button,
		true
	},
	{
		SETTINGS,
		{10, 60},
		{150, 40},
		{125, 125, 125, 255},
		&settings_button,
		false
	},
	{
		OPTIONS,
		{200, 10},
		{150, 40},
		{205, 205, 205, 255},
		&options_button,
		false
	},
	{
		AUDIO,
		{200, 60},
		{150, 40},
		{205, 205, 205, 255},
		&audio_button,
		false
	},
	{
		LANGUAGE,
		{200, 110},
		{150, 40},
		{205, 205, 205, 255},
		&lang_button,
		false
	},
	{
		CONTROLS,
		{200, 160},
		{150, 40},
		{205, 205, 205, 255},
		&controls_button,
		false
	},
	{
		BACK,
		{200, 210},
		{150, 40},
		{205, 205, 205, 255},
		&back_on_title_screen,
		false
	},
	{
		-1,
		{0, 0},
		{0, 0},
		{0, 0, 0, 0},
		NULL,
		false
	}
};
