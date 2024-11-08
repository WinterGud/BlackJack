#include "Board.h"
#include <random>
#include "constants.h"
#include "Renderer.h"

Board::Board()
    : DrawableObject(
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        TABLE_TEXTURE
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
        return nullptr;
    }

    auto card = m_listOfCards.back();
    m_listOfCards.pop_back();
    return card;
}


void Board::shufleDeck()
{
    auto rng = std::default_random_engine(static_cast<unsigned>(std::time(nullptr)));
    std::ranges::shuffle(m_listOfCards, rng);
}
