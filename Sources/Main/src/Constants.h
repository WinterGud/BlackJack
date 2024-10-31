#pragma once
#include <SDL_events.h>
#include <string>

inline struct constants
{
    void resizeVindow(int width, int height);
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
    int CARD_WIDTH = WINDOW_WIDTH / 4;
    int CARD_HEIGHT = WINDOW_HEIGHT / 4;

    const std::string LOG_PATH = "log.txt";
    
} constants;

inline void constants::resizeVindow(int width, int height)
{
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    CARD_WIDTH = WINDOW_WIDTH / 4;
    CARD_HEIGHT = WINDOW_HEIGHT / 4;
}
