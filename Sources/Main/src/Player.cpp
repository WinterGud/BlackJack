#include "Player.h"

#include "CardAssets.h"
#include "Renderer.h"

Player::Player(int balance)
    : m_balance(balance)
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

    if (!m_listOfCards.empty())
    {
        int xNewCard = m_listOfCards.back()->getRect().x + Renderer::getInstance().getWindowParams().getCardWidth();
        int yNewCard = m_listOfCards.back()->getRect().y;
        card.setCoord(xNewCard, yNewCard);
    }
    
    m_listOfCards.push_back(std::make_shared<Card>(std::move(card)));
}
