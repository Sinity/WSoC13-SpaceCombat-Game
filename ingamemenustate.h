#pragma once
#include "game_state.h"

class Sprite;
class IngameMenuState : public GameState
{
public:
    IngameMenuState();
    ~IngameMenuState();

    void handleInput(sf::Event currentEvent);
    void update(sf::Time elapsedTime);

private:
    Sprite* buttonReturnToGame = nullptr;
    Sprite* buttonReturnToMainMenu = nullptr;
    Sprite* buttonQuitGame = nullptr;

    bool returnToGame = false;
    bool returnToMainMenu = false;
    bool quitGame = false;
};
