#pragma once
#include <memory>
#include "Board.h"
#include "Dealer.h"
#include "InputManager.h"
#include "Player.h"
#include "UI.h"

class BlackJack
{
public:
    BlackJack();
    void run();

private:
    void draw() const;
    void update();

    std::shared_ptr<Card> m_card;
    std::shared_ptr<Board> m_board;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Dealer> m_dealer;
    std::shared_ptr<UI> m_ui;

    InputManager m_inputManager;

    bool m_closeGame = false;
};