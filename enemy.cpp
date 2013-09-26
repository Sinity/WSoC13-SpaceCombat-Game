#include "enemy.h"
#include <cmath>
#include "service_locator.h"
#include "emath.h"
#include "gun.h"
#include "player.h"
#include "gameplay_state.h"
#include "engine.h"
#include "particles.h"

Enemy::Enemy(TextureRect image, sf::Vector2f pos, unsigned int attack, unsigned int rateOfFire,
             unsigned int attackRange, unsigned int bulletsSpeed, unsigned int boosterForce,
             float mass, int hp) :
    GameObject(image, pos, 1),
    gun(new Gun(&angle, rateOfFire, attack, attackRange, {50, 50}, bulletsSpeed)),
    engine(new Engine(&angle, &velocity, boosterForce)),
    engineParticles(new ParticlesSource(representation.getPosition()))
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
    this->hp = hp;
    fullHP = hp;
    this->mass = mass;
    this->attack = attack;

    this->maxVelocity = 700.f;

    engine->setMode(EngineMode::Break);
}

Enemy::~Enemy()
{
    delete gun;
    delete engine;

    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();
    state->addExplosion(engineParticles);
}

void Enemy::update(sf::Time elapsedTime)
{
    gun->update(elapsedTime);
    updateAI();
    updatePosition(elapsedTime);

    if(engine->engineMode == EngineMode::Accelerate) {
        engineParticles->position = representation.getPosition();
        auto rlen = ezo::vecLength(-this->resultantForce.x, -this->resultantForce.y);
        sf::Vector2f finalVec = {resultantForce.x / rlen, resultantForce.x / rlen};
        engineParticles->createParticles(20, finalVec, 4.f, sf::Color(250, 20, 20), 3, sf::seconds(0.8f), 0.4f);
    }

    engineParticles->update(elapsedTime);
}

void Enemy::updatePosition(sf::Time elapsedTime)
{
    calculateAngle(elapsedTime, target, fleeFlag);
    addForce(engine->calculateForce(elapsedTime));
    GameObject::updatePosition(elapsedTime);
}

void Enemy::updateAI()
{
    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();
    target = state->player->representation.getPosition();
    updateSteering();
}

void Enemy::fire()
{
    gun->shoot(representation.getPosition());
}

void Enemy::seek()
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
}

void Enemy::flee()
{
    sf::Vector2f targetVec = {representation.getPosition().x - target.x, representation.getPosition().y - target.y};
    float targetLen = ezo::vecLength(targetVec.x, targetVec.y);
    sf::Vector2f targetDir = {targetVec.x/targetLen, targetVec.y/targetLen};
    float targetAngle = -ezo::radToDeg(std::atan2(targetDir.x, targetDir.y));
    if(targetAngle < 0) targetAngle += 360.f;   //normalize angle to 0-360
    fleeFlag = true;
    if(ezo::floatInRange(targetAngle, angle, 30.0f))
        engine->setMode(EngineMode::Break);
    else
        engine->setMode(EngineMode::Accelerate);
}

void Enemy::updateSteering()
{
    switch(steeringMode)
    {
    case SteeringMode::None:
        return;
    case SteeringMode::Stay:
        engine->setMode(EngineMode::Break);
        return;
    case SteeringMode::Seek:
        seek();
        break;
    case SteeringMode::Flee:
        flee();
        break;
    }
}
