#include "Renderer.h"
#include <SDL_image.h>
#include <string>
#include "Constants.h"
#include "Logger.h"

Renderer& Renderer::getInstance()
{
    static Renderer renderer;
    return renderer;
}

SDL_Renderer* Renderer::getRenderer()
{
    return m_renderer;
}

Renderer::~Renderer()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}

Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Logger::getInstance(constants.LOG_PATH).log(
            WARNING, std::string("SDL could not initialize! SDL_Error: %s\n") + SDL_GetError() + '\n');
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        Logger::getInstance(constants.LOG_PATH).log(
            WARNING, std::string("SDL_image could not initialize! IMG_Error: ") + IMG_GetError() + '\n');
    }
    else
    {
        m_window = SDL_CreateWindow(
            "BlackJack",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            constants.WINDOW_WIDTH,
            constants.WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr)
        {
            Logger::getInstance(constants.LOG_PATH).log(
                WARNING, std::string("Window could not be created! SDL_Error: %s\n") + SDL_GetError() + '\n');
        }
        else
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (m_renderer == nullptr)
            {
                Logger::getInstance(constants.LOG_PATH).log(
                    WARNING, std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError() + '\n');
            }
        }
    }
}
