#include <SFML/Graphics.h>

float	isKeyPressed(int keyID, sfRenderWindow *window)
{
	if (window && !sfRenderWindow_hasFocus(window))
		return (0);
	sfJoystick_update();
	if (keyID <= 200) //Normal Key
		return (
			sfKeyboard_isKeyPressed(keyID)
		);

	else if (keyID > 204) //This is a Controller button
		return (
			sfJoystick_isButtonPressed(0, keyID - 205)
		);

	else if (keyID == 201) //Joystick Up
		return (
			sfJoystick_getAxisPosition(0, sfJoystickY) > -3 ?
			0 :
			-sfJoystick_getAxisPosition(0, sfJoystickY) / 100
		);

	else if (keyID == 202) //Joystick Down
		return (
			sfJoystick_getAxisPosition(0, sfJoystickY) < 3 ?
			0 :
			sfJoystick_getAxisPosition(0, sfJoystickY) / 100
		);

	else if (keyID == 203) //Joystick Left
		return (
			sfJoystick_getAxisPosition(0, sfJoystickX) > -3 ?
			0 :
			-sfJoystick_getAxisPosition(0, sfJoystickX) / 100
		);

	return ( //Joystick Right
		sfJoystick_getAxisPosition(0, sfJoystickX) < 3 ?
		0 :
		sfJoystick_getAxisPosition(0, sfJoystickX) / 100
	);
}