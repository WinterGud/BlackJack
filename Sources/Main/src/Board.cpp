#include "Board.h"
#include <random>
#include "CardAssets.h"
#include "Renderer.h"

Board::Board()
    : DrawableObject(
        0,
        0,
        Renderer::getInstance().getWindowParams().getWindowWidth(),
        Renderer::getInstance().getWindowParams().getWindowHeight(),
        cardAssets.TABLE_TEXTURE
    )
{
    
}

Board::~Board()
{
}

void Board::initDeck()
{
    m_listOfCards.clear();
    for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Spades); ++suit) {
        for (int rank = static_cast<int>(Rank::Ace); rank <= static_cast<int>(Rank::King); ++rank) {
            std::string texturePath = generateTexturePath(static_cast<Suit>(suit), static_cast<Rank>(rank));

            m_listOfCards.push_back(std::make_shared<Card>(
                static_cast<Suit>(suit),
                static_cast<Rank>(rank),
                texturePath
            ));
        }
    }
}

void Board::draw()
{
    DrawableObject::draw();
}

void Board::update()
{
}

std::shared_ptr<Card> Board::getCard()
{
    if (m_listOfCards.empty()) {
        return nullptr; // Перевірка на випадок, якщо колода порожня
    }

    auto card = m_listOfCards.back(); // Отримуємо останню карту
    m_listOfCards.pop_back(); // Видаляємо карту з колоди
    return card; // Повертаємо карту як shared_ptr<Card>
}


void Board::shufleDeck()
{
    auto rng = std::default_random_engine(static_cast<unsigned>(std::time(nullptr)));
    std::ranges::shuffle(m_listOfCards, rng);
}
