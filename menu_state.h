#pragma once
#include "game_state.h"

class Sprite;
class MenuState : public GameState
{
public:
    MenuState();
    ~MenuState();

    void handleInput(sf::Event currentEvent);
    void update(sf::Time elapsedTime);
    void resume();

private:
    bool startGame = false;
    bool quitGame = false;

    Sprite* buttonStartGame = nullptr;
    Sprite* buttonQuitGame = nullptr;
    Sprite* background = nullptr;
};
