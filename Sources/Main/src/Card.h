#pragma once
#include "DrawableObject.h"

class Card : public DrawableObject
{
public:
    Card();
    //Card(int x, int y, int h, int w, const std::string& texturePath);
    void draw() override;
    void update() override;
    
private:
    SDL_Texture* m_backTexture;
    bool m_visible = false;
};