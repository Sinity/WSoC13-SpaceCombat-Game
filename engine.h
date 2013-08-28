#pragma once
#include "SFML/System.hpp"

class Engine
{
public:
    Engine(float *angle, unsigned int boosterForcePerSecond);

    sf::Vector2f calculateAfterburnerForce(sf::Time elapsedTime);

private:
    unsigned int boosterForcePerSecond;
    float* angle;
};

