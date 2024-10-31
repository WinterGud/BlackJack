#pragma once
#include <SDL.h>
#include <string>

class DrawableObject
{
public:
    DrawableObject(int x, int y, int h, int w, const std::string& texturePath);
    virtual ~DrawableObject();
    virtual void draw();
    virtual void update() = 0;
    void destroyTexture();

protected:
    SDL_Rect m_rect;
    SDL_Texture* m_mainTexture;
};