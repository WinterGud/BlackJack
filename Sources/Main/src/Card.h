#pragma once
#include "DrawableObject.h"
#include <string>

class Card : public DrawableObject
{
public:
    Card(const std::string& texturePath);
    Card(int x, int y, const std::string& texturePath);
    ~Card() override;

    void draw() override;
    void update() override;

    void show();
    void hide();
    bool isVisible() const;

private:
    SDL_Texture* m_backTexture = nullptr;
    bool m_visible = false;
};
