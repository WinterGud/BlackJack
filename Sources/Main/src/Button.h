#pragma once

#include "DrawableObject.h"
#include <SDL_image.h>
#include "Logger.h"
#include "Renderer.h"
#include "TextureCache.h"
#include <functional>

template <typename ReturnType, typename... Args>
class Button : public DrawableObject
{
public:
    Button(int x, int y, int w, int h, const std::string& mainTexturePath, std::string pressedTexturePath);
    Button(const Button& other);
    ~Button() override;

    void draw() override;
    void update() override;
    void takeFunction(const std::function<void(Args...)>& function);
    bool checkPressed(int x, int y) const;
    void setPressed(bool press) { m_isButtonPressed = press; }

    void triggerFunction(Args... args);

protected:
    bool checkTextures() const override;

    std::string m_pressedTexturePath;
    SDL_Texture* m_pressedTexture;
    bool m_isButtonPressed = false;

private:
    std::function<ReturnType(Args...)> m_callbackFunction;
};


template <typename ReturnType, typename... Args>
::Button<ReturnType, Args...>::Button(int x, int y, int w, int h, const std::string& mainTexturePath,
                                                 std::string pressedTexturePath)
    : DrawableObject(x, y, w, h, mainTexturePath)
      , m_pressedTexturePath(std::move(pressedTexturePath))
      , m_pressedTexture(TexturesCache::getInstance().getTexture(m_pressedTexturePath))

{
}

template <typename ReturnType, typename... Args>
::Button<ReturnType, Args...>::Button(const Button& other)
    : DrawableObject(other)
      , m_pressedTexturePath(other.m_pressedTexturePath)
      , m_pressedTexture(TexturesCache::getInstance().getTexture(m_pressedTexturePath))
      , m_callbackFunction(other.m_callbackFunction)
{
}

template <typename ReturnType, typename... Args>
::Button<ReturnType, Args...>::Button::~Button()
{
    if (m_pressedTexture)
    {
        SDL_DestroyTexture(m_pressedTexture);
        m_pressedTexture = nullptr;
    }
}

template <typename ReturnType, typename... Args>
void ::Button<ReturnType, Args...>::draw()
{
    if (m_isButtonPressed)
    {
        SDL_Texture* textureToDraw = m_isButtonPressed ? m_pressedTexture : m_mainTexture;
        SDL_RenderCopy(Renderer::getInstance().getRenderer(), textureToDraw, nullptr, &m_rect);
    }
    else
    {
        DrawableObject::draw();
    }
}

template <typename ReturnType, typename... Args>
void ::Button<ReturnType, Args...>::update()
{
}

template <typename ReturnType, typename... Args>
void ::Button<ReturnType, Args...>::takeFunction(const std::function<void(Args...)>& function)
{
    m_callbackFunction = function;
}

template <typename ReturnType, typename... Args>
bool ::Button<ReturnType, Args...>::checkPressed(int x, int y) const
{
    return (x >= m_rect.x && x <= m_rect.x + m_rect.w) &&
        (y >= m_rect.y && y <= m_rect.y + m_rect.h);
}

template <typename ReturnType, typename... Args>
void ::Button<ReturnType, Args...>::triggerFunction(Args... args)
{
    if (m_callbackFunction)
    {
        m_callbackFunction(std::forward<Args>(args)...);
    }
    else
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
            "Callback function is not set for the button at position (" +
            std::to_string(m_rect.x) + ", " + std::to_string(m_rect.y) + ")");
    }
}

template <typename ReturnType, typename... Args>
bool ::Button<ReturnType, Args...>::checkTextures() const
{
    if (!DrawableObject::checkTextures() || !m_pressedTexture)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
            "Texture could not be loaded: " + m_pressedTexturePath + "\nIMG_Error: " + IMG_GetError());
        return false;
    }
    return true;
}
