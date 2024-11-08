#include "TextureCache.h"
#include <SDL_image.h>

#include "constants.h"
#include "Logger.h"
#include "Renderer.h"

TexturesCache& TexturesCache::getInstance()
{
    static TexturesCache instance;
    return instance;
}

SDL_Texture* TexturesCache::getTexture(const std::string& texturePath)
{
    auto it = m_textures.find(texturePath);
    if (it != m_textures.end())
    {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Renderer::getInstance().getRenderer(), texturePath.c_str());
    if (texture)
    {
        m_textures[texturePath] = texture;
    }
    else
    {
        Logger::getInstance(LOG_PATH).log(
            WARNING, "Texture could not be loaded: " + texturePath + "\nIMG_Error: " + IMG_GetError());
    }
    return texture;
}

void TexturesCache::clearCache()

{
    for (auto& pair : m_textures)
    {
        SDL_DestroyTexture(pair.second);
    }
    m_textures.clear();
}

TexturesCache::~TexturesCache()
{
}
