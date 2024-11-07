#pragma once
#include <SDL_render.h>
#include <string>

class Renderer
{
public:
    static Renderer& getInstance();
    SDL_Renderer* getRenderer();
    Renderer(const Renderer&) = delete;
    void operator=(const Renderer&) = delete;
    ~Renderer();

    struct WindowParams
    {
        void resizeWindow(int width, int height)
        {
            WINDOW_WIDTH = width;
            WINDOW_HEIGHT = height;
            CARD_WIDTH = WINDOW_WIDTH / 6;
            CARD_HEIGHT = WINDOW_HEIGHT / 4;
        }
        int getWindowWidth() const { return WINDOW_WIDTH; }
        int getWindowHeight() const { return WINDOW_HEIGHT; }
        int getCardWidth() const { return CARD_WIDTH; }
        int getCardHeight() const { return CARD_HEIGHT; }

        const std::string LOG_PATH = "log.txt";
    private:
        int WINDOW_WIDTH = 800;
        int WINDOW_HEIGHT = 600;
        int CARD_WIDTH = WINDOW_WIDTH / 6;
        int CARD_HEIGHT = WINDOW_HEIGHT / 4;
    };

    WindowParams& getWindowParams();

private:
    Renderer();
    inline static SDL_Window* m_window = nullptr;
    inline static SDL_Renderer* m_renderer = nullptr;
    WindowParams m_WindowParams;
};