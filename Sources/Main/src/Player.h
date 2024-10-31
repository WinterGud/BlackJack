#pragma once
#include <memory>
#include <vector>

#include "Card.h"
#include "DrawableObject.h"

class Player
{
public:
    Player(int balance = 1000);
    void update();
    void draw();
    int getBalance() const { return m_balance; }
    
private:
    int m_balance;
    std::shared_ptr<std::vector<Card>> m_listOfCards;
};
