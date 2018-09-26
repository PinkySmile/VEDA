#include <SFML/Graphics.h>
#include "concatf.h"

char	*getKeyString(unsigned char keyID)
{
	switch (keyID) {
	case (unsigned char)sfKeyUnknown:
		return ("None");
	case (unsigned char)sfKeyA:
		return ("A");
	case (unsigned char)sfKeyB:
		return ("B");
	case (unsigned char)sfKeyC:
		return ("C");
	case (unsigned char)sfKeyD:
		return ("D");
	case (unsigned char)sfKeyE:
		return ("E");
	case (unsigned char)sfKeyF:
		return ("F");
	case (unsigned char)sfKeyG:
		return ("G");
	case (unsigned char)sfKeyH:
		return ("H");
	case (unsigned char)sfKeyI:
		return ("I");
	case (unsigned char)sfKeyJ:
		return ("J");
	case (unsigned char)sfKeyK:
		return ("K");
	case (unsigned char)sfKeyL:
		return ("L");
	case (unsigned char)sfKeyM:
		return ("M");
	case (unsigned char)sfKeyN:
		return ("N");
	case (unsigned char)sfKeyO:
		return ("O");
	case (unsigned char)sfKeyP:
		return ("P");
	case (unsigned char)sfKeyQ:
		return ("Q");
	case (unsigned char)sfKeyR:
		return ("R");
	case (unsigned char)sfKeyS:
		return ("S");
	case (unsigned char)sfKeyT:
		return ("T");
	case (unsigned char)sfKeyU:
		return ("U");
	case (unsigned char)sfKeyV:
		return ("V");
	case (unsigned char)sfKeyW:
		return ("W");
	case (unsigned char)sfKeyX:
		return ("X");
	case (unsigned char)sfKeyY:
		return ("Y");
	case (unsigned char)sfKeyZ:
		return ("Z");
	case (unsigned char)sfKeyNum0:
		return ("0");
	case (unsigned char)sfKeyNum1:
		return ("1");
	case (unsigned char)sfKeyNum2:
		return ("2");
	case (unsigned char)sfKeyNum3:
		return ("3");
	case (unsigned char)sfKeyNum4:
		return ("4");
	case (unsigned char)sfKeyNum5:
		return ("5");
	case (unsigned char)sfKeyNum6:
		return ("6");
	case (unsigned char)sfKeyNum7:
		return ("7");
	case (unsigned char)sfKeyNum8:
		return ("8");
	case (unsigned char)sfKeyNum9:
		return ("9");
	case (unsigned char)sfKeyEscape:
		return ("Esc");
	case (unsigned char)sfKeyLControl:
		return ("Left CTRL");
	case (unsigned char)sfKeyRControl:
		return ("Right CTRL");
	case (unsigned char)sfKeyLShift:
		return ("Left Shift");
	case (unsigned char)sfKeyRShift:
		return ("Right Shift");
	case (unsigned char)sfKeyLAlt:
		return ("Left Alt");
	case (unsigned char)sfKeyRAlt:
		return ("Right Alt");
	case (unsigned char)sfKeyLSystem:
		return ("Left OS Key");
	case (unsigned char)sfKeyRSystem:
		return ("Right OS Key");
	case (unsigned char)sfKeyMenu:
		return ("Menu");
	case (unsigned char)sfKeyLBracket:
		return ("[");
	case (unsigned char)sfKeyRBracket:
		return ("]");
	case (unsigned char)sfKeySemiColon:
		return (";");
	case (unsigned char)sfKeyComma:
		return (",");
	case (unsigned char)sfKeyPeriod:
		return (".");
	case (unsigned char)sfKeyQuote:
		return ("'");
	case (unsigned char)sfKeySlash:
		return ("/");
	case (unsigned char)sfKeyBackSlash:
		return ("\\");
	case (unsigned char)sfKeyTilde:
		return ("~");
	case (unsigned char)sfKeyEqual:
		return ("=");
	case (unsigned char)sfKeyDash:
		return ("-");
	case (unsigned char)sfKeySpace:
		return ("Space");
	case (unsigned char)sfKeyReturn:
		return ("Return");
	case (unsigned char)sfKeyBack:
		return ("Backspace");
	case (unsigned char)sfKeyTab:
		return ("Tab");
	case (unsigned char)sfKeyPageUp:
		return ("Page Up");
	case (unsigned char)sfKeyPageDown:
		return ("Page Down");
	case (unsigned char)sfKeyEnd:
		return ("End");
	case (unsigned char)sfKeyHome:
		return ("Home");
	case (unsigned char)sfKeyInsert:
		return ("Insert");
	case (unsigned char)sfKeyDelete:
		return ("Del");
	case (unsigned char)sfKeyAdd:
		return ("+");
	case (unsigned char)sfKeySubtract:
		return ("Minus");
	case (unsigned char)sfKeyMultiply:
		return ("*");
	case (unsigned char)sfKeyDivide:
		return ("Divide");
	case (unsigned char)sfKeyLeft:
		return ("Left Arrow");
	case (unsigned char)sfKeyRight:
		return ("Right Arrow");
	case (unsigned char)sfKeyUp:
		return ("Up Arrow");
	case (unsigned char)sfKeyDown:
		return ("Down Arrow");
	case (unsigned char)sfKeyNumpad0:
		return ("Pad 0");
	case (unsigned char)sfKeyNumpad1:
		return ("Pad 1");
	case (unsigned char)sfKeyNumpad2:
		return ("Pad 2");
	case (unsigned char)sfKeyNumpad3:
		return ("Pad 3");
	case (unsigned char)sfKeyNumpad4:
		return ("Pad 4");
	case (unsigned char)sfKeyNumpad5:
		return ("Pad 5");
	case (unsigned char)sfKeyNumpad6:
		return ("Pad 6");
	case (unsigned char)sfKeyNumpad7:
		return ("Pad 7");
	case (unsigned char)sfKeyNumpad8:
		return ("Pad 8");
	case (unsigned char)sfKeyNumpad9:
		return ("Pad 9");
	case (unsigned char)sfKeyF1:
		return ("F1");
	case (unsigned char)sfKeyF2:
		return ("F2");
	case (unsigned char)sfKeyF3:
		return ("F3");
	case (unsigned char)sfKeyF4:
		return ("F4");
	case (unsigned char)sfKeyF5:
		return ("F5");
	case (unsigned char)sfKeyF6:
		return ("F6");
	case (unsigned char)sfKeyF7:
		return ("F7");
	case (unsigned char)sfKeyF8:
		return ("F8");
	case (unsigned char)sfKeyF9:
		return ("F9");
	case (unsigned char)sfKeyF10:
		return ("F10");
	case (unsigned char)sfKeyF11:
		return ("F11");
	case (unsigned char)sfKeyF12:
		return ("F12");
	case (unsigned char)sfKeyF13:
		return ("F13");
	case (unsigned char)sfKeyF14:
		return ("F14");
	case (unsigned char)sfKeyF15:
		return ("F15");
	case (unsigned char)sfKeyPause:
		return ("Pause");
	case 201:
		return ("Joystick Up");
	case 202:
		return ("Joystick Down");
	case 203:
		return ("Joystick Left");
	case 204:
		return ("Joystick Right");
	default:
		if (keyID >= 205)
			return (concatf("Con. Button %i", keyID - 205));
		return (concatf("Key %i", keyID));
	}
}