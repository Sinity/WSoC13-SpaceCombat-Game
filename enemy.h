#pragma once
#include "game_object.h"

class Player;
class Bullet;
class Enemy : public GameObject
{
public:
    Enemy(TextureRect image, sf::Vector2f pos, Player* player);
	virtual ~Enemy(){}

    virtual void update(sf::Time elapsedTime);

	virtual void updatePosition(sf::Time elapsedTime);
	virtual void calculateAfterburnerForce(sf::Time elapsedTime);

    virtual void updateAI(sf::Time elapsedTime, Player* player);
    std::vector<Bullet*> bullets;
    void shoot(sf::Vector2f target);

protected:
    Player* player = nullptr;
    unsigned int attack;

	//booster stuff
	bool afterburnerActive = true;
	unsigned int boosterForcePerSecond = 100000000;
    sf::Vector2f boosterForce;
	
	sf::Vector2f destination;

    //weapon
    const sf::Time haltDuration;
    sf::Clock clock;
    sf::Time haltAccumulator;
};
