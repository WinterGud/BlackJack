#include "Renderer.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "constants.h"
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
        Logger::getInstance(LOG_PATH).log(WARNING, "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) + '\n');
    }
    else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        Logger::getInstance(LOG_PATH).log(WARNING, "SDL_image could not initialize! IMG_Error: " + std::string(IMG_GetError()) + '\n');
    }
    else if (TTF_Init() == -1)
    {
        Logger::getInstance(LOG_PATH).log(WARNING, "SDL_TTF could not initialize! TTF_Error: " + std::string(TTF_GetError()) + '\n');
    }
    else
    {
        m_window = SDL_CreateWindow("BlackJack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr)
        {
            Logger::getInstance(LOG_PATH).log(WARNING, "Window could not be created! SDL_Error: " + std::string(SDL_GetError()) + '\n');
        }
        else
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (m_renderer == nullptr)
            {
                Logger::getInstance(LOG_PATH).log(WARNING, "Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()) + '\n');
            }
        }
    }
}