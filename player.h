#pragma once
#include "game_object.h"

class Gun;
class Engine;
class DrawableVector;
class ParticlesSource;
class Player : public GameObject
{
public:
    Player(TextureRect data, sf::Vector2f position);
    ~Player();
    void update(sf::Time elapsedTime);

    void updatePosition(sf::Time elapsedTime);
    void shoot();

    Gun* gun = nullptr;
    Engine* engine = nullptr;

    unsigned int score;
private:
    ParticlesSource* engineParticles;
};
