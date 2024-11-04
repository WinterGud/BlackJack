#pragma once
#include <list>
#include "Button.h"

class UI
{
public:
    void update();
    void draw();

    bool checkAndPressButtonsPressed(int x, int y);

private:
    std::list<Button<void()>> m_listOfButtons;
    
};
