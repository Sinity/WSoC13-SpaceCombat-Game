#pragma once
#include "enemy.h"

class Ship : public Enemy
{
public:
    Ship(sf::Vector2f position, unsigned int hp, unsigned int radarRadious, unsigned int weaponRadious, unsigned int attack, unsigned int rateOfFire, float mass, unsigned int speed);

    void updateAI(sf::Time elapsedTime);
private:
    unsigned int radarRadious;
    unsigned int weaponRadious;

    enum class State
    {
        chase,
        stay,
        fire,
        escape
    } state = State::stay;

};

