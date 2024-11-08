#pragma once
#include <list>
#include <memory>
#include "Card.h"
#include "Coord.h"

class Player 
{
public:
    Player(int balance = 500, int x = 0, int y = 0);
    void update();
    void draw() const;
    void takeCard(Card& card);
    int getBalance() const { return m_balance; }
    void modifyBalance(int balance) { m_balance += balance; }
    int getBet() const { return m_bet; }
    virtual void centerCards();
    void setBet(int bet);
    Coord getNextCardCoord() const { return m_nextCardCoord; }
    void setWin(bool win) { m_winRound = win; }
    bool getWinRound() const { return m_winRound; }
    int getCardPoints() { countCardPoints(); return m_CardPoints; }
    int getNumOfCards() const { return static_cast<int>(m_listOfCards.size()); }
    void showCards() const;
    void clearCards();

protected:
    void countCardPoints();

    bool m_winRound = false;
    Coord m_coordToCenterCards;
    Coord m_nextCardCoord;
    int m_balance;
    int m_CardPoints = 0;
    int m_bet = 0;
    std::list<std::shared_ptr<Card>> m_listOfCards;
    
};
