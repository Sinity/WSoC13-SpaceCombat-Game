#include "bullet.h"
#include "textureRect.h"
#include "ezolib.h"
#include "service_locator.h"
#include "gameplay_state.h"

Bullet::Bullet(TextureRect texrect, sf::Vector2f position, sf::Vector2f direction, float range, unsigned int attack, unsigned speed) :
    GameObject(texrect, position, 1), attack(attack), range(range), speed(speed), initPosition(position)
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
    representation.setPosition(position);
    maxVelocity = 1500;
    velocity = { direction.x * speed, direction.y * speed };
}

void Bullet::update(sf::Time elapsedTime)
{
    GameObject::update(elapsedTime);

    sf::Vector2f distVec = representation.getPosition() - initPosition;
    float distVecLen = ezo::vecLength(distVec.x, distVec.y);
    if(distVecLen > range)
        destroy();
}

void Bullet::destroy()
{
    GameplayState* state = (GameplayState*)servLoc.getEngine()->states.back();

    state->addExplosion(100, representation.getPosition(), 3.f);

    GameObject::destroy();
}
