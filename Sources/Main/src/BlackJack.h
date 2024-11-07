#pragma once
#include <memory>
#include "Board.h"
#include "InputManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "UI.h"

class BlackJack
{
public:
    BlackJack();
    ~BlackJack();
    void run();
    void push();

private:
    void init() const;
    void draw() const;
    void update();

    void takeCard(Player& player, bool cardVisiable) const;
    void animateCardMove(const Player& player, const std::shared_ptr<DrawableObject>& card, double targetX, double targetY, double duration) const;

    
    InputManager m_inputManager;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Player> m_dealer;
    std::shared_ptr<UI> m_ui;
    std::shared_ptr<Board> m_board;
    std::shared_ptr<SoundManager> m_soundManager;

    int id = 0;

    bool m_closeGame = false;
};