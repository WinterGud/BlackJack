#include "Card.h"
#include <SDL_image.h>
#include "constants.h"
#include "Logger.h"
#include "Renderer.h"
#include "TextureCache.h"

Card::Card(Suit suit, Rank rank, const std::string& texturePath)
    : DrawableObject(
          WINDOW_WIDTH,
          WINDOW_HEIGHT,
          CARD_WIDTH,
          CARD_HEIGHT,
          texturePath)
      , m_backTexturePath(CARD_BACK_TEXTURE)
      , m_backTexture(TexturesCache::getInstance().getTexture(m_backTexturePath))
      , m_suit(suit)
      , m_rank(rank)
{
    if (!m_backTexture)
    {
        Logger::getInstance(LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + m_backTexturePath + "\nIMG_Error: " + IMG_GetError());
    }
}

Card::Card(Suit suit, Rank rank, int x, int y, const std::string& texturePath)
    : DrawableObject(
          x,
          y,
          CARD_WIDTH,
          CARD_HEIGHT,
          texturePath)
      , m_backTexturePath(CARD_BACK_TEXTURE)
      , m_backTexture(TexturesCache::getInstance().getTexture(m_backTexturePath))
      , m_suit(suit)
      , m_rank(rank)
{
    if (!m_backTexture)
    {
        Logger::getInstance(LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + CARD_BACK_TEXTURE + "\nIMG_Error: " + IMG_GetError());
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
