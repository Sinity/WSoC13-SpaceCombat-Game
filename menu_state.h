#pragma once
#include "game_state.h"

class Sprite;
class MenuState : public GameState
{
public:
    MenuState();
    ~MenuState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);
    void resume();

private:
    Sprite* menu_start = nullptr;
    Sprite* menu_highscores = nullptr;
    Sprite* menu_quit = nullptr;

    Sprite* background = nullptr;
};
