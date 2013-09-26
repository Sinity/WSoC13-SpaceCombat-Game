#pragma once
#include "drawable.h"
#include <vector>
#include <SFML/Graphics.hpp>

struct Particle
{
    Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color color, sf::Time life) : position(pos), velocity(vel), color(color), life(life){}
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    sf::Time life;
};

class ParticlesSource : public Drawable
{
public:
    ParticlesSource(sf::Vector2f position, int level = 0);
    ~ParticlesSource();

    void draw(sf::RenderWindow* window);
    void update(sf::Time dt);

    void createParticles(unsigned count, sf::Vector2f baseVelocity, float velocityDelta, sf::Color color,
                         int colorDelta, sf::Time life, float lifeDelta);

    sf::Vector2f position;

    size_t empty() { return particles.empty(); }

private:
    std::vector<Particle> particles;
    std::minstd_rand randEngine = std::minstd_rand(time(0));
};
