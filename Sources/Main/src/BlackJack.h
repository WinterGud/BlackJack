#pragma once
#include <memory>
#include "Board.h"
#include "Button.h"
#include "Dealer.h"
#include "InputManager.h"
#include "Player.h"
#include "UI.h"

class BlackJack
{
public:
    BlackJack();
    ~BlackJack();
    void run();

private:
    void init();
    void draw() const;
    void update();
    
    InputManager m_inputManager;
    std::shared_ptr<DrawableObject> m_obj;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<UI> m_ui;
    Button<int, int>* m_button;

    int id = 0;

    bool m_closeGame = false;
};