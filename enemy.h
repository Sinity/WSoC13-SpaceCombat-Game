#pragma once
#include "game_object.h"

class Player;
class Gun;
class Enemy : public GameObject
{
public:
    Enemy(TextureRect image, sf::Vector2f pos);
    virtual ~Enemy();

    virtual void update(sf::Time elapsedTime);

	virtual void updatePosition(sf::Time elapsedTime);
	virtual void calculateAfterburnerForce(sf::Time elapsedTime);

    virtual void updateAI(sf::Time elapsedTime);

    void fire(sf::Vector2f target);
    Gun* gun;

protected:
	//booster stuff
	bool afterburnerActive = true;
	unsigned int boosterForcePerSecond = 100000000;
	
    //ai stuff
	sf::Vector2f destination;
};
