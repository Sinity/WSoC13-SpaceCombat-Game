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
    void shoot(sf::Vector2f target);

    Gun* gun = nullptr;
    Engine* engine = nullptr;

private:
    ParticlesSource* engineParticles;

    DrawableVector* velocityVec = nullptr;
};
