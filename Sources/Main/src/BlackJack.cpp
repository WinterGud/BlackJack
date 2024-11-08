#include "BlackJack.h"
#include <thread>
#include "Renderer.h"
#include "constants.h"

namespace 
{
    constexpr int PLAYER_CENTER_X = (WINDOW_WIDTH - CARD_WIDTH) / 2;
    constexpr int PLAYER_CENTER_Y = WINDOW_HEIGHT / 1.8;
    constexpr int DEALER_CENTER_X = PLAYER_CENTER_X;
    constexpr int DEALER_CENTER_Y = WINDOW_HEIGHT * 0.2;
}

BlackJack::BlackJack()
    : m_inputManager()
    , m_player(std::make_shared<Player>(1000, PLAYER_CENTER_X, PLAYER_CENTER_Y))
    , m_dealer(std::make_shared<Player>(1000000, DEALER_CENTER_X, DEALER_CENTER_Y))
    , m_ui(std::make_shared<UI>())
    , m_board(std::make_shared<Board>())
    , m_soundManager(std::make_shared<SoundManager>())
{
    init();
}

BlackJack::~BlackJack()
{
    TexturesCache::getInstance().clearCache();
}

void BlackJack::run()
{
    while (!m_closeGame)
    {
        update();
        draw();
    }
}

void BlackJack::init() const
{
    m_soundManager->init();
    std::function<void()> hitFunc = [&]()
    {
        m_soundManager->playButtonPressSound();
        if (m_player->getBet() > 0)
        {
            if (m_player->getNumOfCards() < 2)
            {
                m_player->modifyBalance(-m_player->getBet());
                m_ui->lockBets();
                takeCard(*m_player, true);
                takeCard(*m_player, true);
                takeCard(*m_dealer, true);
                takeCard(*m_dealer, false);
            }
            else
            {
                takeCard(*m_player, true);
            }
        }
    };
    
    std::function<void()> standFunc = [&]()
    {
        m_soundManager->playButtonPressSound();
        if (m_player->getNumOfCards() >= 2 && m_player->getBet() > 0)
        {
            m_dealer->showCards();

            while (m_dealer->getCardPoints() < 17)
            {
                takeCard(*m_dealer, true);
            }

            int playerPoints = m_player->getCardPoints();
            int dealerPoints = m_dealer->getCardPoints();

            if (dealerPoints > 21 || playerPoints > dealerPoints)
            {
                m_player->modifyBalance(m_player->getBet() * 2);
                m_player->setWin(true);
            }
            else if (dealerPoints == playerPoints)
            {
                m_player->modifyBalance(m_player->getBet());
                m_player->setWin(false);
            }
            else
            {
                m_player->setWin(false);
            }

           SDL_Delay(500);
            m_player->setBet(-m_player->getBet());
            m_ui->unlockBets();
            m_board->initDeck();
            m_board->shufleDeck();
            m_player->clearCards();
            m_dealer->clearCards();
        }
    };

    std::function<void()> increaseBetFunc = [&]()
    {
        m_player->setBet(5);
    };
    
    std::function<void()> decreaseBetFunc = [&]()
    {
        m_player->setBet(-5);
    };

    m_ui->init(hitFunc, standFunc, increaseBetFunc, decreaseBetFunc);
    m_board->initDeck();
    m_board->shufleDeck();
}

void BlackJack::draw() const
{
    SDL_RenderClear(Renderer::getInstance().getRenderer());
    m_board->draw();
    m_player->draw();
    m_dealer->draw();
    m_ui->draw(m_player->getBalance(), m_player->getBet());
    SDL_RenderPresent(Renderer::getInstance().getRenderer());
}

void BlackJack::update()
{
    m_inputManager.update();
    m_closeGame = m_inputManager.getQuit();
    m_player->update();
    m_dealer->update();
    m_ui->update(m_inputManager.getMouseCoord().x, m_inputManager.getMouseCoord().y, m_inputManager.getLeftMousePressed());
    m_board->update();
}

void BlackJack::takeCard(Player& player, bool cardVisiable) const
{
    std::shared_ptr<Card> playerCard = std::make_shared<Card>(*m_board->getCard());
    if (cardVisiable)
    {
        playerCard->show();
    }
    animateCardMove(
        player,
        playerCard,
        m_player->getNextCardCoord().x,
        m_player->getNextCardCoord().y,
        1.0);
    player.takeCard(*playerCard);
}

void BlackJack::animateCardMove(const Player& player, const std::shared_ptr<DrawableObject>& card, double targetX, double targetY, double duration) const
{
    double startX = card->getRect().x;
    double startY = card->getRect().y;
    
    Coord nextCardCoord = player.getNextCardCoord();
    targetX = nextCardCoord.x;
    targetY = nextCardCoord.y;
    
    double deltaX = targetX - startX;
    double deltaY = targetY - startY;

    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - startTime;
        double t = elapsedTime.count() / duration;

        if (t >= 1.0)
        {
            card->setCoord(static_cast<int>(targetX), static_cast<int>(targetY));
            break;
        }
        
        int currentX = static_cast<int>(startX + deltaX * t);
        int currentY = static_cast<int>(startY + deltaY * t);
        
        draw();

        card->setCoord(currentX, currentY);
        card->draw();
        
        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }
}

