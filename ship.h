#pragma once
#include "enemy.h"

class Ship : public Enemy
{
public:
    Ship(sf::Vector2f position, unsigned int hp, unsigned int radarRadious, unsigned int weaponRadious);

    void updateAI(sf::Time elapsedTime);
private:
    unsigned int radarRadious;
    unsigned int weaponRadious;

    enum state
    {
        chase,
        stay,
        fire,
        escape
    } state = stay;

};

