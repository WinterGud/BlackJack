#include "Card.h"
#include <SDL_image.h>
#include "CardAssets.h"
#include "Constants.h"
#include "Logger.h"
#include "Renderer.h"

Card::Card()
    : DrawableObject(
          100,
          100,
          constants.CARD_WIDTH,
          constants.CARD_HEIGHT,
          cardAssets.testFront)
      , m_backTexture(IMG_LoadTexture(
          Renderer::getInstance().getRenderer(),
          cardAssets.testBack.c_str()))
{
    if (!m_mainTexture)
    {
        Logger::getInstance(constants.LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + cardAssets.testBack + "\nIMG_Error: " + IMG_GetError());
    }
}

void Card::draw()
{
    if (m_visible)
    {
        DrawableObject::draw();
    }
    else
    {
        SDL_RenderCopy(
            Renderer::getInstance().getRenderer(),
            m_backTexture,
            nullptr,
            &m_rect);
    }
}

void Card::update()
{
}
