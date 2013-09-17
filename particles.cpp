#include "particles.h"
#include "service_locator.h"

ParticlesSource::ParticlesSource(sf::Vector2f position, int level) : position(position),
    Drawable(level)
{
    servLoc.getRender()->addObj(this);
}

ParticlesSource::~ParticlesSource()
{
    servLoc.getRender()->removeObj(this);
}

void ParticlesSource::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow *window)
{
    sf::VertexArray points(sf::Points, particles.size());
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        points[i].position = particles[i].position;
        points[i].color = particles[i].color;
    }

    window->draw(points);
}

void ParticlesSource::update(sf::Time dt)
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].life -= dt;
        if(particles[i].life <= sf::Time::Zero)
        {
            particles.erase(particles.begin()+i);
            continue;
        }
        particles[i].position += particles[i].velocity;
    }
}

void ParticlesSource::createParticles(unsigned count, sf::Vector2f baseVelocity, float velocityDelta,
                                      sf::Color color, int colorDelta, sf::Time life, float lifeDelta)
{
    std::uniform_real_distribution<float> velRandDist(-velocityDelta, +velocityDelta);
    std::uniform_int_distribution<int> colRandDist(-colorDelta, +colorDelta);
    std::uniform_real_distribution<float>  lifeRandDist(-lifeDelta, +lifeDelta);

    for(unsigned int i = 0; i < count; i++)
    {
        sf::Vector2f finalVel;
        sf::Color finalColor;
        sf::Time finalLifetime;

        finalVel = {baseVelocity.x + velRandDist(randEngine), baseVelocity.y + velRandDist(randEngine)};
        finalColor = {color.r + colRandDist(randEngine), color.g + colRandDist(randEngine), color.b + colRandDist(randEngine)};
        finalLifetime = sf::Time(life + sf::seconds(lifeRandDist(randEngine)));

        particles.emplace_back(this->position, finalVel, finalColor, finalLifetime);
    }
}
