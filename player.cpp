#include "player.h"
#include "service_locator.h"
#include "drawablevector.h"
#include "gun.h"
#include "engine.h"
#include "particles.h"
#include "ezolib.h"

Player::Player(TextureRect data, sf::Vector2f position) :
    GameObject(data, position, 1),
    gun(new Gun(&angle, 5, 10, 700, {50, 50})),
    engine(new Engine(&angle, &velocity, 1000000000)),
    engineParticles(new ParticlesSource(representation.getPosition()))
{
    hp = 100;
    fullHP = hp;
    mass = 10000;

    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
}

void Player::update(sf::Time elapsedTime)
{
    gun->update(elapsedTime);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        shoot(sf::Vector2f(0, 0));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        engine->setMode(EngineMode::Accelerate);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        engine->setMode(EngineMode::Break);
    else
        engine->setMode(EngineMode::Nothing);

    sf::Vector2f mousePosition = servLoc.getRender()->getWindow()->mapPixelToCoords(
                                     sf::Mouse::getPosition(*servLoc.getRender()->getWindow()));
    calculateAngle(elapsedTime, mousePosition, false);
    updatePosition(elapsedTime);

    if(engine->engineMode == EngineMode::Accelerate) {
        engineParticles->position = representation.getPosition();
        auto rlen = ezo::vecLength(-this->resultantForce.x, -this->resultantForce.y);
        sf::Vector2f finalVec = {resultantForce.x / rlen, resultantForce.x / rlen};
        engineParticles->createParticles(50, finalVec, 4.f, sf::Color(5, 250, 250), 4, sf::seconds(3.f), 2.5f);
    }

    engineParticles->update(elapsedTime);
}

void Player::updatePosition(sf::Time elapsedTime)
{
    addForce(engine->calculateForce(elapsedTime));
    GameObject::updatePosition(elapsedTime);
    representation.setPosition(representation.getPosition());
}

void Player::shoot(sf::Vector2f target)
{
    gun->shoot(representation.getPosition());
}

Player::~Player()
{
    delete gun;
    delete engine;
    delete engineParticles;
}


