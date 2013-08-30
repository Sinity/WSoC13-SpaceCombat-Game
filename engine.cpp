#include "engine.h"
#include "ezolib.h"

Engine::Engine(float* angle, sf::Vector2f* velocity, unsigned int boosterForcePerSecond) :
    boosterForcePerSecond(boosterForcePerSecond),
    angle(angle),
    velocity(velocity)
{
}

sf::Vector2f Engine::calculateForce(sf::Time elapsedTime)
{
    switch(engineMode)
    {
        case EngineMode::Accelerate:
            return calculateAfterburnerForce(elapsedTime);
        case EngineMode::Break:
            return calculateBreakForce(elapsedTime);
        case EngineMode::Nothing:
        default:    //warning bypass
            return {0.f, 0.f};
    }
}

sf::Vector2f Engine::calculateAfterburnerForce(sf::Time elapsedTime)
{
    return sf::Vector2f((float)sin(ezo::degToRad(*angle)) * elapsedTime.asSeconds() * boosterForcePerSecond,
                        (float)-cos(ezo::degToRad(*angle)) * elapsedTime.asSeconds() * boosterForcePerSecond);
}

sf::Vector2f Engine::calculateBreakForce(sf::Time elapsedTime)
{
    float velLen = ezo::vecLength( velocity->x, velocity->y);
    if(velLen < 0.1)
    {
        velocity->x = velocity->y = 0.f;
        return {0.f, 0.f};
    }
    sf::Vector2f unitCounterVel = {velocity->x / velLen, velocity->y / velLen };
    unitCounterVel = -unitCounterVel;
    sf::Vector2f afterburnerForce = calculateAfterburnerForce(elapsedTime);
    float afterburnerForceVel = ezo::vecLength(afterburnerForce.x, afterburnerForce.y);
    return {afterburnerForceVel * unitCounterVel.x, afterburnerForceVel * unitCounterVel.y};
}
