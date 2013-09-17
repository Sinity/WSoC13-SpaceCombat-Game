#pragma once
#include "game_object.h"

class Bullet : public GameObject
{
public:
    Bullet(TextureRect texrect, sf::Vector2f position, sf::Vector2f direction, float range, unsigned int attack, unsigned speed = 1500);

    virtual void update(sf::Time elapsedTime);

    unsigned int attack; //damage dealed by this bullet
    float range;
    unsigned int speed;

    sf::Vector2f initPosition;
};
