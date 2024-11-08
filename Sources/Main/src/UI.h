#pragma once
#include <SDL_ttf.h>
#include "Button.h"

class UI
{
public: 
    UI();
    void init(const std::function<void()>& hitFunc, const std::function<void()>& standFunc, const std::function<void()>&
              increaseBetFunc, const std::function<void()>& decreaseBetFunc) const;
    void update(int x, int y, bool mousePressed);
    void draw(int playerBalance, int playerBet) const;
    void lockBets() const;
    void unlockBets() const;
    
private:
    void drawText(const std::string& text, int x, int y, SDL_Color color) const;
    
    std::shared_ptr<Button<void>> m_hitButton;
    std::shared_ptr<Button<void>> m_standButton;
    std::shared_ptr<Button<void>> m_increaseBetButton;
    std::shared_ptr<Button<void>> m_decreaseBetButton ;
    TTF_Font* m_font; 
};
