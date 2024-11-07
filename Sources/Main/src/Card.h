#pragma once
#include "DrawableObject.h"
#include <string>
#include "CardEnums.h"

class Card : public DrawableObject
{
public:
    Card(Suit suit, Rank rank, const std::string& texturePath);
    Card(Suit suit, Rank rank, int x, int y, const std::string& texturePath);
    ~Card() override;

    void draw() override;
    void update() override;

    void show();
    void hide();
    bool isVisible() const;
    Rank getRank() const { return m_rank; }
    int getValue() { return toInt(m_rank); }

private:
    std::string m_backTexturePath;
    SDL_Texture* m_backTexture = nullptr;
    bool m_visible = false;
    Suit m_suit;
    Rank m_rank;
};
