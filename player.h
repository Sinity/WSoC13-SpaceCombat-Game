#pragma once
#include "game_object.h"

class Gun;
class Player : public GameObject
{
public:
	Player(TextureRect data, sf::Vector2f position);
    ~Player();

	void draw(sf::Time t, sf::RenderWindow* r);
	
	//Physical stuff
	void updatePosition(sf::Time elapsedTime);
    void calculateAfterburnerForce(bool afterburnerKeyPressed, sf::Time elapsedTime);

    void shoot(sf::Vector2f target);

    void update(sf::Time elapsedTime);

    Gun* gun = nullptr;

private:
	unsigned int boosterForcePerSecond;
};
