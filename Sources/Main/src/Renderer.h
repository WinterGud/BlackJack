#pragma once
#include <SDL_render.h>

class Renderer
{
public:
    static Renderer& getInstance();
    SDL_Renderer* getRenderer();
    Renderer(const Renderer&) = delete;
    void operator=(const Renderer&) = delete;
    ~Renderer();

private:
    Renderer();
    inline static SDL_Window* m_window = nullptr;
    inline static SDL_Renderer* m_renderer = nullptr;
};
