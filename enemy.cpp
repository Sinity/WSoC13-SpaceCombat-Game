#include "enemy.h"
#include <cmath>
#include "service_locator.h"
#include "emath.h"
#include "bullet.h"
#include "player.h"

Enemy::Enemy(TextureRect image, sf::Vector2f pos, Player* player) :
    GameObject(image, pos, 1), player(player)
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
	hp = 1;
    fullHP = 1;
    mass = 10000;
}

void Enemy::update(sf::Time elapsedTime)
{
    updateAI(elapsedTime, player);
    updatePosition(elapsedTime);
}

void Enemy::updatePosition(sf::Time elapsedTime)
{
	calculateAfterburnerForce(elapsedTime);
	GameObject::updatePosition(elapsedTime);
}

void Enemy::updateAI(sf::Time elapsedTime, Player* player)
{
    destination = player->representation.getPosition();
    calculateAngle(elapsedTime, destination);
}

void Enemy::calculateAfterburnerForce(sf::Time elapsedTime)
{
    if (afterburnerActive) //turn on booster
    {
		boosterForce = {(float)sin(ezo::degToRad(angle)) * elapsedTime.asSeconds()  * boosterForcePerSecond,
						(float)-cos(ezo::degToRad(angle)) * elapsedTime.asSeconds() * boosterForcePerSecond};
		addForce(boosterForce);
    }
}

void Enemy::shoot(sf::Vector2f target)
{
    haltAccumulator += clock.restart();
    if(haltAccumulator > haltDuration)
    {
        sf::Vector2f shootDirection((float)sin(ezo::degToRad(angle)),
                                    (float)-cos(ezo::degToRad(angle)));

        Bullet* b = new Bullet(servLoc.getResourceManager()->getTextureRect("ship"), //good is * bullet.width/height(probably) + costam (down)
            sf::Vector2f(representation.getPosition().x+shootDirection.x*50, representation.getPosition().y+shootDirection.y*50), shootDirection, 5000, attack);

        b->setAngle(this->angle);
        bullets.push_back(b);

        haltAccumulator = sf::microseconds(0);
    }
}
