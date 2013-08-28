#pragma once
#include "game_object.h"

class Player;
class Gun;
class Engine;
class Enemy : public GameObject
{
public:
    Enemy(TextureRect image, sf::Vector2f pos, unsigned int attack, unsigned int rateOfFire,
          unsigned int attackRange, unsigned int bulletsSpeed, unsigned int boosterForce,
          float mass, int hp);
    virtual ~Enemy();

    virtual void update(sf::Time elapsedTime);

	virtual void updatePosition(sf::Time elapsedTime);

    virtual void updateAI(sf::Time elapsedTime);

    void fire(sf::Vector2f target);
    Gun* gun;

protected:
	//booster stuff
	bool afterburnerActive = true;
    Engine* engine;
	
    //ai stuff
	sf::Vector2f destination;
};
