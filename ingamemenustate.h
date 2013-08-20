#pragma once
#include "game_state.h"

class Sprite;
class IngameMenuState : public GameState
{
public:
    IngameMenuState();
    ~IngameMenuState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);

private:
    Sprite* menu_return = nullptr;
    Sprite* menu_main = nullptr;
    Sprite* menu_quit = nullptr;

    Sprite* under_menu = nullptr;
};
