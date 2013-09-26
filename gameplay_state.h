#pragma once
#include "game_state.h"
#include <random>
#include <ctime>
#include "SFML/System.hpp"

class Player;
class Level;
class Sprite;
class Bar;
class Text;
class Enemy;
class ParticlesSource;
class GameplayState : public GameState
{
public:
    GameplayState();
    ~GameplayState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);

    void addExplosion(unsigned count, sf::Vector2f position, float radious);
    void addExplosion(ParticlesSource* emiter);

    Player* player = nullptr;
private:
    Bar* playerHP;
    Text* score;

    void updateObjects(sf::Time elapsedTime);
    void resolveCollisions();
    void cleanForces();
    void resolveExistance();

    std::vector<Enemy*> enemies;

private:
    std::vector<ParticlesSource*> explosions;

    std::minstd_rand randEngine = std::minstd_rand(time(0));
};

