#include "Player.h"
#include "Renderer.h"

Player::Player(int balance, int x, int y)
    : m_coordToCenterCards(x, y)
      , m_nextCardCoord(x, y)
      , m_balance(balance)
{
}

void Player::update()
{
    
}

void Player::draw() const
{
    for (const auto& card : m_listOfCards)
    {
        card->draw();
    }
}

void Player::takeCard(Card& card)
{
    m_listOfCards.push_back(std::make_shared<Card>(card));
    centerCards();
}

void Player::centerCards()
{
    int windowWidth = Renderer::getInstance().getWindowParams().getWindowWidth();
    int cardWidth = Renderer::getInstance().getWindowParams().getCardWidth();

    int totalCardsWidth = cardWidth + (cardWidth / 2.5) * (m_listOfCards.size() - 1);
    int startX = (windowWidth - totalCardsWidth) / 2;
    int yPosition = m_coordToCenterCards.y;
    
    int currentX = startX;
    if (m_listOfCards.empty())
    {
        m_nextCardCoord.x = currentX;
        m_nextCardCoord.y = yPosition;
        return;
    }
    
    for (auto& card : m_listOfCards)
    {
        card->setCoord(currentX, yPosition);
        currentX += cardWidth / 2.5;
    }

    m_nextCardCoord.x = currentX;
    m_nextCardCoord.y = yPosition;
}



void Player::setBet(int bet)
{
    m_bet += bet;
    if (m_bet < 0)
    {
        m_bet = 0;
    }
}

void Player::showCards() const
{
    for (auto& card : m_listOfCards)
    {
        card->show();
    }
}

void Player::clearCards()
{
    m_listOfCards.clear();
    m_CardPoints = 0;
}

void Player::countCardPoints()
{
    int points = 0;
    int aceCount = 0;

    for (const auto& card : m_listOfCards)
    {
        int cardValue = card->getValue();
        
        if (cardValue >= 2 && cardValue <= 10)
        {
            points += cardValue;
        }
        else if (cardValue >= 11 && cardValue <= 13)
        {
            points += 10;
        }
        else if (cardValue == 1)
        {
            points += 11;
            aceCount++;
        }
    }

    while (points > 21 && aceCount > 0)
    {
        points -= 10;
        aceCount--;
    }

    m_CardPoints = points; 
}

