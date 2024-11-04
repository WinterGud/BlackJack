#include "DrawableObject.h"
#include <SDL_image.h>
#include "Logger.h"
#include "Renderer.h"
#include "TextureCache.h"

DrawableObject::DrawableObject(int x, int y, int w, int h, std::string texturePath)
    : m_mainTexturePath(std::move(texturePath))
    , m_rect{x, y, w, h}
    , m_mainTexture(TexturesCache::getInstance().getTexture(m_mainTexturePath))

{
}

DrawableObject::DrawableObject(SDL_Rect rect, std::string mainTexturePath)
    : m_mainTexturePath(std::move(mainTexturePath))
      , m_rect(rect)
{
    m_mainTexture = TexturesCache::getInstance().getTexture(m_mainTexturePath);
}

DrawableObject::~DrawableObject()
{
    if (DrawableObject::checkTextures())
    {
        SDL_DestroyTexture(m_mainTexture);
        m_mainTexture = nullptr;
    }
}

DrawableObject::DrawableObject(const DrawableObject& other)
    : m_mainTexturePath(other.m_mainTexturePath)
    , m_rect(other.m_rect)
{
    if (other.checkTextures())
    {
        m_mainTexture = TexturesCache::getInstance().getTexture(m_mainTexturePath);
    }
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
    return *this;
}

void DrawableObject::draw()
{
    if (checkTextures())
    {
        SDL_RenderCopy(Renderer::getInstance().getRenderer(), m_mainTexture, nullptr, &m_rect);
    }
    else
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING, "Attempted to draw without a valid texture");
    }
}

bool DrawableObject::checkTextures() const
{
    if (!m_mainTexture)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
            "Texture could not be loaded: " + m_mainTexturePath + "\nIMG_Error: " + IMG_GetError());
        return false;
    }
    return true;
}
