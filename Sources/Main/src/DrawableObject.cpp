#include "DrawableObject.h"

#include <chrono>
#include <SDL_image.h>
#include <thread>

#include "constants.h"
#include "Logger.h"
#include "Renderer.h"
#include "TextureCache.h"

DrawableObject::DrawableObject(int x, int y, int w, int h, const std::string& mainTexturePath)
    : m_mainTexturePath(std::move(mainTexturePath))
      , m_rect{x, y, w, h}
      , m_mainTexture(TexturesCache::getInstance().getTexture(m_mainTexturePath))
{
    DrawableObject::logTextures();
}

DrawableObject::DrawableObject(SDL_Rect rect, const std::string& mainTexturePath)
    : m_mainTexturePath(std::move(mainTexturePath))
      , m_rect(rect)
{
    m_mainTexture = TexturesCache::getInstance().getTexture(m_mainTexturePath);
    DrawableObject::logTextures();
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::moveAnimation(double targetX, double targetY, double duration)
{
    double startX = m_rect.x;
    double startY = m_rect.y;

    double deltaX = targetX - startX;
    double deltaY = targetY - startY;

    auto startTime = std::chrono::high_resolution_clock::now();
    SDL_Rect previousRect = m_rect;

    SDL_SetRenderDrawBlendMode(Renderer::getInstance().getRenderer(), SDL_BLENDMODE_BLEND);

    while (true)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - startTime;
        double t = elapsedTime.count() / duration;

        if (t >= 1.0)
        {
            setCoord(static_cast<int>(targetX), static_cast<int>(targetY));
            break;
        }

        int currentX = static_cast<int>(startX + deltaX * t);
        int currentY = static_cast<int>(startY + deltaY * t);

        SDL_SetRenderDrawColor(Renderer::getInstance().getRenderer(), 0, 0, 0, 0); // прозорий фон
        SDL_RenderFillRect(Renderer::getInstance().getRenderer(), &previousRect);

        setCoord(currentX, currentY);
        draw();

        previousRect = m_rect;

        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }
}


DrawableObject::DrawableObject(const DrawableObject& other)
    : m_mainTexturePath(other.m_mainTexturePath)
      , m_rect(other.m_rect)
{
    if (other.m_mainTexture)
    {
        m_mainTexture = TexturesCache::getInstance().getTexture(m_mainTexturePath);
    }
    DrawableObject::logTextures();
}

DrawableObject& DrawableObject::operator=(const DrawableObject& other)
{
    if (this != &other)
    {
        m_rect = other.m_rect;
        m_mainTexturePath = other.m_mainTexturePath;
        if (other.m_mainTexture)
        {
            m_mainTexture = TexturesCache::getInstance().getTexture(m_mainTexturePath);
        }
    }
    DrawableObject::logTextures();
    return *this;
}

void DrawableObject::draw()
{
    if (m_mainTexture)
    {
        SDL_RenderCopy(
            Renderer::getInstance().getRenderer(),
            m_mainTexture,
            nullptr,
            &m_rect);
    }
    else
    {
        Logger::getInstance(LOG_PATH).log(
            WARNING,
            std::string("\nIMG_Error: ") + IMG_GetError());
    }
}

void DrawableObject::logTextures() const
{
    if (!m_mainTexture)
    {
        Logger::getInstance(LOG_PATH).log(
            WARNING,
            "Texture could not be loaded: " + m_mainTexturePath + "\nIMG_Error: " + IMG_GetError());
    }
    else
    {
        Logger::getInstance(LOG_PATH).log(
            INFO,
            "Texture was loaded successfully: " + m_mainTexturePath);
    }
}
