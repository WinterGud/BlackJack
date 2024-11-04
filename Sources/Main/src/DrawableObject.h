#pragma once
#include <SDL.h>
#include <string>

class DrawableObject
{
public:
    DrawableObject(int x, int y, int w, int h, std::string texturePath);
    DrawableObject(SDL_Rect rect, std::string mainTexturePath);
    DrawableObject(const DrawableObject& other);
    DrawableObject& operator=(const DrawableObject& other);
    virtual ~DrawableObject();

    virtual void draw();
    virtual void update() = 0;
    
    SDL_Rect getRect() const { return m_rect; }
    void setCoord(int x, int y) { m_rect.x = x; m_rect.y = y; }
    
protected:
    std::string m_mainTexturePath;
    SDL_Rect m_rect;
    SDL_Texture* m_mainTexture;

    virtual bool checkTextures() const;
};

