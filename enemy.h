#pragma once
#include "game_object.h"

class Player;
class Gun;
class Engine;
class ParticlesSource;
class Enemy : public GameObject
{
public:
    Enemy(TextureRect image, sf::Vector2f position, unsigned int attack, unsigned int rateOfFire,
          unsigned int attackRange, unsigned int bulletsSpeed, unsigned int boosterForce,
          float mass, int hp);
    virtual ~Enemy();

    virtual void update(sf::Time elapsedTime);
    virtual void updatePosition(sf::Time elapsedTime);
    virtual void updateAI();

    void fire();
    Gun* gun;

    void seek();
    void flee();

    unsigned attack;
protected:
    enum class SteeringMode {
        None,
        Stay,
        Seek,
        Flee
    } steeringMode = SteeringMode::None;
    sf::Vector2f target;
    bool fleeFlag = false;
    void updateSteering();

    Engine* engine;
    ParticlesSource* engineParticles;
};
