#include "BlackJack.h"
#include <thread>
#include "CardAssets.h"
#include "Renderer.h"

BlackJack::BlackJack()
    : m_inputManager()
    , m_player(std::make_shared<Player>())
{
    init();
}

BlackJack::~BlackJack()
{
    delete m_button;
}

void BlackJack::run()
{
    while (!m_closeGame)
    {
        draw();
        update();
    }
}

void BlackJack::init()
{
    m_button = new Button<void, int>(
        100,
        100,
        100,
        100,
        cardAssets.testFront,
        cardAssets.TABLE_TEXTURE);
    std::function<void(int)> func = [](int id)
    {
        std::cout << "Button pressed with ID: " << id << '\n';
    };
    m_button->takeFunction(func);
}

void BlackJack::draw() const
{
    SDL_RenderClear(Renderer::getInstance().getRenderer());

    m_button->draw();
    SDL_RenderPresent(Renderer::getInstance().getRenderer());
}

void BlackJack::update()
{
    m_inputManager.update();
    m_closeGame = m_inputManager.getQuit();
    if (m_inputManager.getLeftMousePressed())
    {
        if (m_button->checkPressed(
            m_inputManager.getMouseCoord().x,
            m_inputManager.getMouseCoord().y))
        {
            m_button->setPressed(true);
            m_button->triggerFunction(id++);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    else
    {
        m_button->setPressed(false);
    }
}
