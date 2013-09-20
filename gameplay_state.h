#pragma once
#include "game_state.h"

class Player;
class Level;
class Sprite;
class Bar;
class Text;
class GameplayState : public GameState
{
public:
    GameplayState();
    ~GameplayState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);

    void setLevel(unsigned int levelID);

    Player* player = nullptr;
    Bar* playerHP;
    Text* score;

private:
    void updateObjects(sf::Time elapsedTime);
    void resolveCollisions();
    void cleanForces();

    std::vector<Level*> levels;
    Level* currentLevel = nullptr;
};

