#pragma once
#include <list>
#include <memory>
#include "Card.h"

class Player 
{
public:
    Player(int balance = 1000);
    void update();
    void draw() const;
    void takeCard(Card& card);
    int getBalance() const { return m_balance; }
    
private:
    int m_balance;
    int m_amountPoints = 0;
    std::list<std::shared_ptr<Card>> m_listOfCards;
    
};
