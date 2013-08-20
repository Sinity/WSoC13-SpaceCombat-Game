#pragma once
#include "game_object.h"

class Bullet : public GameObject
{
public:
	Bullet(TextureRect texrect, sf::Vector2f position, sf::Vector2f direction, float speed, unsigned int attack);
    unsigned int attack; //damage dealed by this bullet
};
