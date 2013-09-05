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
    calculateAngle(elapsedTime, target, flee);
    addForce(engine->calculateForce(elapsedTime));
    GameObject::updatePosition(elapsedTime);
}

void Enemy::updateAI(sf::Time elapsedTime)
{
    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();
    target = state->player->representation.getPosition();
    updateSteering(elapsedTime);
}

void Enemy::fire()
{
    gun->shoot(representation.getPosition());
}

void Enemy::updateSteering(sf::Time elapsedTime)
{
    switch(steeringMode)
    {
    case SteeringMode::None:
        return;
    case SteeringMode::Stay:
        engine->setMode(EngineMode::Break);
        return;
    case SteeringMode::Seek:
    {
        sf::Vector2f targetVec = {representation.getPosition().x - target.x, representation.getPosition().y - target.y};
        float targetLen = ezo::vecLength(targetVec.x, targetVec.y);
        sf::Vector2f targetDir = {targetVec.x/targetLen, targetVec.y/targetLen};
        float targetAngle = -ezo::radToDeg(std::atan2(targetDir.x, targetDir.y));
        if(targetAngle < 0) targetAngle += 360.f;   //normalize angle to 0-360
        if(ezo::floatInRange(targetAngle, angle, 5.0f))
            engine->setMode(EngineMode::Accelerate);
        else
            engine->setMode(EngineMode::Break);
        break;
    }
    case SteeringMode::Flee:
    {
        sf::Vector2f targetVec = {representation.getPosition().x - target.x, representation.getPosition().y - target.y};
        float targetLen = ezo::vecLength(targetVec.x, targetVec.y);
        sf::Vector2f targetDir = {targetVec.x/targetLen, targetVec.y/targetLen};
        float targetAngle = -ezo::radToDeg(std::atan2(targetDir.x, targetDir.y));
        if(targetAngle < 0) targetAngle += 360.f;   //normalize angle to 0-360
        flee = true;
        if(ezo::floatInRange(targetAngle, angle, 30.0f))
            engine->setMode(EngineMode::Break);
        else
            engine->setMode(EngineMode::Accelerate);
        break;
    }
    }
}
