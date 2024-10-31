#include "DrawableObject.h"
#include <SDL_image.h>

#include "Constants.h"
#include "Logger.h"
#include "Renderer.h"

DrawableObject::DrawableObject(int x, int y, int h, int w, const std::string& texturePath)
    : m_rect{x, y, h, w}
      , m_mainTexture(IMG_LoadTexture(
          Renderer::getInstance().getRenderer(),
          texturePath.c_str()))
{
    if (!m_mainTexture)
    {
        Logger::getInstance(constants.LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + texturePath + "\nIMG_Error: " + IMG_GetError());
    }
}

DrawableObject::~DrawableObject()
{
    destroyTexture();
}

void DrawableObject::draw()
{
    SDL_RenderCopy(
        Renderer::getInstance().getRenderer(),
        m_mainTexture,
        nullptr,
        &m_rect);
}

void DrawableObject::destroyTexture()
{
    if (m_mainTexture)
    {
        SDL_DestroyTexture(m_mainTexture);
        m_mainTexture = nullptr;
    }
}
