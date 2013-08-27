#include "enemy.h"
#include <cmath>
#include "service_locator.h"
#include "emath.h"
#include "gun.h"
#include "player.h"
#include "gameplay_state.h"

Enemy::Enemy(TextureRect image, sf::Vector2f pos) :
    GameObject(image, pos, 1),
    gun(new Gun(&angle, 10, 1, 600.f, {50, 50}, 300))
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
	hp = 1;
    fullHP = 1;
    mass = 10000;
}

Enemy::~Enemy()
{
    delete gun;
}

void Enemy::update(sf::Time elapsedTime)
{
    gun->update(elapsedTime);

    updateAI(elapsedTime);
    updatePosition(elapsedTime);
}

void Enemy::updatePosition(sf::Time elapsedTime)
{
    calculateAngle(elapsedTime, destination);
    calculateAfterburnerForce(elapsedTime);
    GameObject::updatePosition(elapsedTime);
}

void Enemy::updateAI(sf::Time elapsedTime)
{
    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();
    destination = state->player->representation.getPosition();
    fire(destination);
}

void Enemy::calculateAfterburnerForce(sf::Time elapsedTime)
{
    if (afterburnerActive)
    {
        sf::Vector2f boosterForce = {(float)sin(ezo::degToRad(angle)) * elapsedTime.asSeconds()  * boosterForcePerSecond,
						(float)-cos(ezo::degToRad(angle)) * elapsedTime.asSeconds() * boosterForcePerSecond};
		addForce(boosterForce);
    }
}

void Enemy::fire(sf::Vector2f target)
{
    gun->shoot(target, representation.getPosition());
}
