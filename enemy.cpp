#include "enemy.h"
#include <cmath>
#include "service_locator.h"
#include "emath.h"
#include "gun.h"
#include "player.h"
#include "gameplay_state.h"
#include "engine.h"

Enemy::Enemy(TextureRect image, sf::Vector2f pos, unsigned int attack, unsigned int rateOfFire,
             unsigned int attackRange, unsigned int bulletsSpeed, unsigned int boosterForce,
             float mass, int hp) :
    GameObject(image, pos, 1),
    gun(new Gun(&angle, rateOfFire, attack, attackRange, {50, 50}, bulletsSpeed)),
    engine(new Engine(&angle, &velocity, boosterForce))
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
    this->hp = hp;
    fullHP = hp;
    this->mass = mass;

    engine->setMode(EngineMode::Break);
}

Enemy::~Enemy()
{
    delete gun;
    delete engine;
}

void Enemy::update(sf::Time elapsedTime)
{
    gun->update(elapsedTime);

    updateAI(elapsedTime);
    updatePosition(elapsedTime);
}

void Enemy::updatePosition(sf::Time elapsedTime)
{
    calculateAngle(elapsedTime, target);
    addForce(engine->calculateForce(elapsedTime));
    GameObject::updatePosition(elapsedTime);
}

void Enemy::updateAI(sf::Time elapsedTime)
{
    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();
    target = state->player->representation.getPosition();
    fire(target);
}

void Enemy::fire(sf::Vector2f target)
{
    gun->shoot(target, representation.getPosition());
}
