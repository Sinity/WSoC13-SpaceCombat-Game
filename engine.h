#pragma once
#include "SFML/System.hpp"

enum class EngineMode {
    Accelerate,
    Break,
    Nothing
};

class Engine
{
public:
    Engine(float *angle, sf::Vector2f* velocity, unsigned int boosterForcePerSecond);

    void setMode(EngineMode mode) { engineMode = mode; }
    sf::Vector2f calculateForce(sf::Time elapsedTime);

private:
    unsigned int boosterForcePerSecond;
    float* angle;
    sf::Vector2f* velocity;

    sf::Vector2f calculateAfterburnerForce(sf::Time elapsedTime);
    sf::Vector2f calculateBreakForce(sf::Time elapsedTime);

    EngineMode engineMode = EngineMode::Break;
};

