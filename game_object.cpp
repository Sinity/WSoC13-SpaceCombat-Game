#include "game_object.h"
#include "service_locator.h"
#include "ezolib.h"

GameObject::GameObject(TextureRect texrect, sf::Vector2f position, unsigned int level) :
    Drawable(level),
    representation(texrect, position, level)
{
    servLoc.getRender()->addObj(this);
}

void GameObject::updatePosition(sf::Time elapsedTime)
{
    sf::Vector2f acceleration(resultantForce.x / mass, resultantForce.y / mass);
	
    //calculate velocity
    sf::Vector2f newVelocity = velocity + acceleration*elapsedTime.asSeconds();
	float newVelocityLen = ezo::vecLength(newVelocity.x, newVelocity.y);
	if(newVelocityLen > maxVelocity)
        velocity = {newVelocity.x/newVelocityLen*maxVelocity, newVelocity.y/newVelocityLen*maxVelocity};
	else
		velocity = newVelocity;
		
    oldPosition = representation.getPosition();
    representation.setPosition(representation.getPosition() + velocity*elapsedTime.asSeconds());
}

void GameObject::addForce(sf::Vector2f f)
{
	resultantForce += f;
}

void GameObject::hit(unsigned int _hp)
{
	if(_hp > hp)
		destroy();
	else
		hp -= _hp;
}

void GameObject::destroy()
{
    servLoc.getRender()->removeObj(this);
    servLoc.getRender()->removeObj(&representation);
    exist = false;
}

void GameObject::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow *window)
{
}

void GameObject::calculateAngle(sf::Time elapsedTime, sf::Vector2f target)
{
    servLoc.getProfiler()->start("calculateAngle()");

    float maxDelta = this->deltaAngle * elapsedTime.asSeconds();

    float newAngle = (float)-(atan2(representation.getPosition().x - target.x, representation.getPosition().y - target.y));
    newAngle = ezo::radToDeg(newAngle);
    if(newAngle < 0) newAngle += 360;

    float dAngle = newAngle - angle;
    if(dAngle > 180) dAngle -= 360;
        else if(dAngle < -180) dAngle += 360;
    if(dAngle > maxDelta) dAngle = maxDelta;
        else if(dAngle < -maxDelta) dAngle = -maxDelta;

    angle += dAngle;
    if(angle < 0.f) angle += 360.f;
        else if(angle > 360.f) angle -= 360.f;
    representation.setRotation(angle);

    servLoc.getProfiler()->stop();
}

void GameObject::setAngle(float angle)
{
    this->angle = angle;
    representation.setRotation(angle);
}

void GameObject::update(sf::Time elapsedTime)
{
    updatePosition(elapsedTime);
}
