#include "Card.h"
#include <SDL_image.h>
#include "CardAssets.h"
#include "Logger.h"
#include "Renderer.h"
#include "TextureCache.h"


Card::Card(const std::string& texturePath)
    : DrawableObject(
      100,
      100,
      Renderer::getInstance().getWindowParams().getCardWidth(),
      Renderer::getInstance().getWindowParams().getCardHeight(),
      texturePath)
    , m_backTexture(TexturesCache::getInstance().getTexture(texturePath))
{
    if (!m_backTexture)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + cardAssets.CARD_BACK_TEXTURE + "\nIMG_Error: " + IMG_GetError());
    }
}

Card::Card(int x, int y, const std::string& texturePath)
    : DrawableObject(
      x,
      y,
      Renderer::getInstance().getWindowParams().getCardWidth(),
      Renderer::getInstance().getWindowParams().getCardHeight(),
      texturePath)
    , m_backTexture(IMG_LoadTexture(
      Renderer::getInstance().getRenderer(),
      cardAssets.CARD_BACK_TEXTURE.c_str()))
{
    if (!m_backTexture)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + cardAssets.CARD_BACK_TEXTURE + "\nIMG_Error: " + IMG_GetError());
    }
}

Card::~Card()
{
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

void Card::show()
{
    m_visible = true;
}

void Card::hide()
{
    m_visible = false;
}

bool Card::isVisible() const
{
    return m_visible;
}
