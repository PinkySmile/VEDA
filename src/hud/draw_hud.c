#include <utils.h>
#include "display.h"

void	displayHUD()
{
	if (getPlayer()) {
		drawEnergyBar();
		drawLifeBar();
	}
}