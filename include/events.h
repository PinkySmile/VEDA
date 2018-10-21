#ifndef VEDA_EVENTS_H
#define VEDA_EVENTS_H

#include <SFML/Window.h>

void	manageEventClosed();
void	manageJoystickMoved();
void	manageMouseReleased();
void	manageKeyPressed(sfEvent *event);
void	manageMouseMoved(sfEvent *event);
void	manageTextEntered(sfEvent *event);
void	manageJoystickButtonPressed(sfEvent *event);

#endif //VEDA_EVENTS_H
