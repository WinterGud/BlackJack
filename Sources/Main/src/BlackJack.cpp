#include "BlackJack.h"

#include "Renderer.h"


BlackJack::BlackJack()
    : m_card(std::make_shared<Card>())
      , m_board(std::make_shared<Board>())
      , m_player(std::make_shared<Player>())
      , m_dealer(std::make_shared<Dealer>())
{
}

void BlackJack::run()
{
    while (m_player->getBalance() > 0 && !m_closeGame)
    {
        draw();
        update();
    }
}

void BlackJack::draw() const
{
    SDL_RenderClear(Renderer::getInstance().getRenderer());
    m_card->draw();
    SDL_RenderPresent(Renderer::getInstance().getRenderer());
}

void BlackJack::update()
{
    m_inputManager.update();
    m_closeGame = m_inputManager.getQuit();
}
