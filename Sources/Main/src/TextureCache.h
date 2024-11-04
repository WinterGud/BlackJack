#pragma once
#include <unordered_map>
#include <string>
#include <SDL.h>

class TexturesCache
{
public:
    static TexturesCache& getInstance();
    SDL_Texture* getTexture(const std::string& texturePath);
    void clearCache();

private:
    std::unordered_map<std::string, SDL_Texture*> m_textures;
    TexturesCache() = default;
    ~TexturesCache();
};
