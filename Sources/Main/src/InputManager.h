#pragma once
#include <SDL_events.h>
#include "Coord.h"

class InputManager
{
public:
    void update();
    bool getQuit() const;
    Coord getMouseCoord() const;
    bool getLeftMousePressed() const;
    bool getLeftMouseUnPressed() const;

protected:
    SDL_Event m_event;

    bool m_quit = false;
    Coord m_mouseCoord = Coord(0, 0);
    bool m_leftMousePressed = false;
    bool m_leftMouseUnPressed = false;
};
