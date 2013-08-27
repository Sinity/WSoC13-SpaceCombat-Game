#include "player.h"
#include <cmath>
#include "emath.h"
#include "service_locator.h"
#include "drawablevector.h"
#include "gun.h"

void Player::updatePosition(sf::Time elapsedTime)
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    calculateAfterburnerForce(spacePressed, elapsedTime);
	
    GameObject::updatePosition(elapsedTime);
    representation.setPosition(representation.getPosition());
}

void Player::calculateAfterburnerForce(bool afterburnerKeyPressed, sf::Time elapsedTime)
{
	if(afterburnerKeyPressed)
	{
        sf::Vector2f boosterForce((float)sin(ezo::degToRad(angle)) * elapsedTime.asSeconds() * boosterForcePerSecond,
                                     (float)-cos(ezo::degToRad(angle)) * elapsedTime.asSeconds() * boosterForcePerSecond);
		                            
		addForce(boosterForce);
	}
}

Player::Player(TextureRect data, sf::Vector2f position) :
	GameObject(data, position, 1),
    gun(new Gun(&angle, 10, 10, 500, {50, 50})),
    boosterForcePerSecond(1000000000)
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
	mass = 10000;
}

void Player::update(sf::Time elapsedTime)
{
    gun->update(elapsedTime);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        shoot(sf::Vector2f(0, 0));
		
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        destroy();

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
}


