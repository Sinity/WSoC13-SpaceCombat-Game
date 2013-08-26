#pragma once
#include "game_object.h"

class Bullet;
class Player : public GameObject
{
public:
	Player(TextureRect data, sf::Vector2f position);
	
	void draw(sf::Time t, sf::RenderWindow* r);
	
	//Physical stuff
	void updatePosition(sf::Time elapsedTime);
    void calculateAfterburnerForce(bool afterburnerKeyPressed, sf::Time elapsedTime);

    void shoot(sf::Vector2f target);

    void update(sf::Time elapsedTime);

    std::vector<Bullet*> bullets;
private:
	unsigned int boosterForcePerSecond;

    //weapon
    const sf::Time haltDuration;
    sf::Clock clock;
    sf::Time haltAccumulator;
};
