#pragma once
#include "game_object.h"

class Gun;
class Engine;
class DrawableVector;
class Player : public GameObject
{
public:
	Player(TextureRect data, sf::Vector2f position);
    ~Player();
    void update(sf::Time elapsedTime);

	void updatePosition(sf::Time elapsedTime);
    void shoot(sf::Vector2f target);

    Gun* gun = nullptr;

private:
    Engine* engine = nullptr;
    DrawableVector* velocityVec = nullptr;
};
