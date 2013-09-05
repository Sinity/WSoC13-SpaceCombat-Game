#pragma once
#include "SFML/System.hpp"
#include <vector>


class Bullet;
class Gun
{
public:
    Gun(const float* baseAngle, float shootsPerSecond, int attack, float range,
        sf::Vector2f differencePosition = {0, 0}, unsigned int speed = 2100, float differenceAngle = 0);
    ~Gun();

    void shoot(sf::Vector2f basePosition);
    void update(sf::Time elapsedTime);

    std::vector<Bullet*> bullets;

private:
    sf::Vector2f* position;
    sf::Vector2f diffPosition;

    const float* baseAngle;
    float diffAngle;

    const sf::Time haltDuration;
    sf::Clock clock;
    sf::Time haltAccumulator;

    int attack;
    unsigned int speed;
    unsigned int range;
};
