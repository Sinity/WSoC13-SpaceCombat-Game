#pragma once
#include "game_object.h"

class Portal : public GameObject
{
public:
    Portal(unsigned int destinationID, sf::Vector2f position);
    unsigned int destinationID;
};
