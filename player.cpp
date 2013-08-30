#include "player.h"
#include "service_locator.h"
#include "drawablevector.h"
#include "gun.h"
#include "engine.h"

void Player::updatePosition(sf::Time elapsedTime)
{
    addForce(engine->calculateForce(elapsedTime));
    GameObject::updatePosition(elapsedTime);
    representation.setPosition(representation.getPosition());
}

Player::Player(TextureRect data, sf::Vector2f position) :
	GameObject(data, position, 1),
    gun(new Gun(&angle, 10, 1, 500, {50, 50})),
    engine(new Engine(&angle, &velocity, 1000000000))
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
    calculateAngle(elapsedTime, mousePosition);
    updatePosition(elapsedTime);
}

void Player::shoot(sf::Vector2f target)
{
    gun->shoot(target, representation.getPosition());
}

void Player::draw(sf::Time t, sf::RenderWindow* r)
{
    servLoc.getProfiler()->start("drawing player");

	GameObject::draw(t, r);
	
    DrawableVector velocityVec(velocity+representation.getPosition(), representation.getPosition());
    velocityVec.draw(t, r);

    servLoc.getProfiler()->stop();
}

Player::~Player()
{
    delete gun;
    delete engine;
}


