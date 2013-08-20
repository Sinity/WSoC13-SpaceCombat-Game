#pragma once
#include "enemy.h"

class Ship : public Enemy
{
public:
    Ship(sf::Vector2f position, Player* player, unsigned int hp, unsigned int attack, unsigned int radarRadious, unsigned int weaponRadious);

    void updateAI(sf::Time elapsedTime, Player* player);
private:
    unsigned int radarRadious;
    unsigned int weaponRadious;

    enum state
    {
        chase,
        stay,
        shoot,
        escape
    }state = stay;

};

