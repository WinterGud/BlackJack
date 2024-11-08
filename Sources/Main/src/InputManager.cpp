#include "InputManager.h"

#include "Renderer.h"

void InputManager::update()
{
    while (SDL_PollEvent(&m_event) != 0)
    {
        switch (m_event.type)
        {
        case SDL_QUIT:
            m_quit = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouseUnPressed = false;
                m_leftMousePressed = true;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouseUnPressed = true;
                m_leftMousePressed = false;
            }
            break;

        case SDL_MOUSEMOTION:
            m_mouseCoord.x = m_event.motion.x;
            m_mouseCoord.y = m_event.motion.y;
            break;

        case SDL_WINDOWEVENT:
            if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int newWidth = m_event.window.data1;
                int newHeight = m_event.window.data2;
            }
        }
    }
}

bool InputManager::getQuit() const
{
    return m_quit;
}

Coord InputManager::getMouseCoord() const
{
    return m_mouseCoord;
}

bool InputManager::getLeftMousePressed() const
{
    return m_leftMousePressed;
}

bool InputManager::getLeftMouseUnPressed() const
{
    return m_leftMouseUnPressed;
}
