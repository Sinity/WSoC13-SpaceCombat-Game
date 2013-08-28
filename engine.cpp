#include "engine.h"
#include "ezolib.h"

Engine::Engine(float* angle, unsigned int boosterForcePerSecond) :
    boosterForcePerSecond(boosterForcePerSecond),
    angle(angle)
{
}

sf::Vector2f Engine::calculateAfterburnerForce(sf::Time elapsedTime)
{
    return sf::Vector2f((float)sin(ezo::degToRad(*angle)) * elapsedTime.asSeconds() * boosterForcePerSecond,
                        (float)-cos(ezo::degToRad(*angle)) * elapsedTime.asSeconds() * boosterForcePerSecond);
}
