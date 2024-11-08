#pragma once
#include <memory>
#include <vector>
#include "Card.h"
#include "DrawableObject.h"

class Board : public DrawableObject
{
public:
    Board();
    ~Board() override;
    void initDeck();
    void draw() override;
    void update() override;
    std::shared_ptr<Card> getCard();
    void shufleDeck();

private:
    std::vector<std::shared_ptr<Card>> m_listOfCards;
};
