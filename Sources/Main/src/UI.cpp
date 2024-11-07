#include "UI.h"
#include <thread>
#include "CardAssets.h"
#include <SDL_ttf.h>

#include "Fonts.h"

namespace
{
    const int BUTTON_WIDTH = Renderer::getInstance().getWindowParams().getWindowWidth() / 8;
    const int BUTTON_HEIGHT = Renderer::getInstance().getWindowParams().getWindowHeight() / 8;
    const int HIT_BUTTON_X_POSITION = Renderer::getInstance().getWindowParams().getWindowWidth() / 1.2;
    const int HIT_BUTTON_Y_POSITION = Renderer::getInstance().getWindowParams().getWindowHeight() / 3;
    const int STAND_BUTTON_X_POSITION = Renderer::getInstance().getWindowParams().getWindowWidth() / 1.2;
    const int STAND_BUTTON_Y_POSITION = Renderer::getInstance().getWindowParams().getWindowHeight() / 3 + BUTTON_HEIGHT;
    const int INCREASE_BET_BUTTON_X_POSITION = Renderer::getInstance().getWindowParams().getWindowWidth() / 15;
    const int INCREASE_BET_BUTTON_Y_POSITION = Renderer::getInstance().getWindowParams().getWindowHeight() / 3;
    const int DECREASE_BET_BUTTON_X_POSITION = Renderer::getInstance().getWindowParams().getWindowWidth() / 15;
    const int DECREASE_BET_BUTTON_Y_POSITION = Renderer::getInstance().getWindowParams().getWindowHeight() / 3 + BUTTON_HEIGHT;
    const std::string HIT_BUTTON_PATH = cardAssets.testFront;
    const std::string HIT_BUTTON_PRESSED_PATH = cardAssets.CARD_BACK_TEXTURE;
    const std::string STAND_BUTTON_PATH = cardAssets.TABLE_TEXTURE;
    const std::string STAND_BUTTON_PRESSED_PATH = cardAssets.CARD_BACK_TEXTURE;
    const std::string INCREASE_BET_BUTTON_PATH = cardAssets.CARD_BACK_TEXTURE;
    const std::string INCREASE_BET_BUTTON_PRESSED_PATH = cardAssets.CARD_BACK_TEXTURE;
    const std::string DECREASE_BET_BUTTON_PATH = cardAssets.CARD_BACK_TEXTURE;
    const std::string DECREASE_BET_BUTTON_PRESSED_PATH = cardAssets.CARD_BACK_TEXTURE;
}

UI::UI()
{
    m_font = TTF_OpenFont(fonts.BaseFont.c_str(), 24);
    if (!m_font)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            ERROR,
            "Failed to load font: " + std::string(TTF_GetError())
        );
    }
    m_hitButton = std::make_shared<Button<void>>(
        HIT_BUTTON_X_POSITION,
        HIT_BUTTON_Y_POSITION,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        HIT_BUTTON_PATH,
        HIT_BUTTON_PRESSED_PATH);

    m_standButton = std::make_shared<Button<void>>(
        STAND_BUTTON_X_POSITION,
        STAND_BUTTON_Y_POSITION,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        STAND_BUTTON_PATH,
        STAND_BUTTON_PRESSED_PATH);

    m_increaseBetButton = std::make_shared<Button<void>>(
        INCREASE_BET_BUTTON_X_POSITION,
        INCREASE_BET_BUTTON_Y_POSITION,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        INCREASE_BET_BUTTON_PATH,
        INCREASE_BET_BUTTON_PRESSED_PATH);

    m_decreaseBetButton = std::make_shared<Button<void>>(
        DECREASE_BET_BUTTON_X_POSITION,
        DECREASE_BET_BUTTON_Y_POSITION,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        DECREASE_BET_BUTTON_PATH,
        DECREASE_BET_BUTTON_PRESSED_PATH);
}

void UI::init(const std::function<void()>& hitFunc, const std::function<void()>& standFunc,
              const std::function<void()>& increaseBetFunc, const std::function<void()>& decreaseBetFunc) const
{
    m_hitButton->takeFunction(hitFunc);
    m_standButton->takeFunction(standFunc);
    m_increaseBetButton->takeFunction(increaseBetFunc);
    m_decreaseBetButton->takeFunction(decreaseBetFunc);
}

void UI::update(int x, int y, bool mousePressed)
{
    if (mousePressed)
    {
        if (m_hitButton->checkPressed(x, y))
        {
            m_hitButton->setPressed(true);
            m_hitButton->triggerFunction();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if (m_standButton->checkPressed(x, y))
        {
            m_standButton->setPressed(true);
            m_standButton->triggerFunction();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if (m_increaseBetButton->checkPressed(x, y))
        {
            m_increaseBetButton->setPressed(true);
            m_increaseBetButton->triggerFunction();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        else if (m_decreaseBetButton->checkPressed(x, y))
        {
            m_decreaseBetButton->setPressed(true);
            m_decreaseBetButton->triggerFunction();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
    else
    {
        m_hitButton->setPressed(false);
        m_standButton->setPressed(false);
        m_increaseBetButton->setPressed(false);
        m_decreaseBetButton->setPressed(false);
    }
}


void UI::draw(int playerBalance, int playerBet) const
{
    m_hitButton->draw();
    m_standButton->draw();
    m_increaseBetButton->draw();
    m_decreaseBetButton->draw();

    SDL_Color whiteColor = {255, 255, 255, 255};  // Білий колір тексту
    drawText("Balance: " + std::to_string(playerBalance), 50, 20, whiteColor);
    drawText("Bet: " + std::to_string(playerBet), 50, 60, whiteColor);
}

void UI::lockBets() const
{
    m_increaseBetButton->lock();
    m_decreaseBetButton->lock();
}

void UI::unlockBets() const
{
    m_increaseBetButton->unLock();
    m_decreaseBetButton->unLock();
}

void UI::drawText(const std::string& text, int x, int y, SDL_Color color) const
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), textSurface);
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};

    SDL_RenderCopy(Renderer::getInstance().getRenderer(), textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
