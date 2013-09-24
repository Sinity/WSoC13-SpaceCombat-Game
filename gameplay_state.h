#pragma once
#include "game_state.h"
#include <random>

class Player;
class Level;
class Sprite;
class Bar;
class Text;
class Enemy;
class GameplayState : public GameState
{
public:
    GameplayState();
    ~GameplayState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);

    Player* player = nullptr;
private:
    Bar* playerHP;
    Text* score;

    void updateObjects(sf::Time elapsedTime);
    void resolveCollisions();
    void cleanForces();
    void resolveExistance();

    std::vector<Enemy*> enemies;

    std::minstd_rand randEngine = std::minstd_rand(time(0));
};

