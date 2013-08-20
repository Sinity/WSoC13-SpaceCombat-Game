#pragma once
#include "sprite.h"

class GameObject : public Drawable
{
public:
	GameObject(TextureRect texrect, sf::Vector2f position, unsigned int level);
	
    virtual void update(sf::Time elapsedTime);

    virtual void updatePosition(sf::Time elapsedTime);
    void addForce(sf::Vector2f f);

    void calculateAngle(sf::Time elapsedTime, sf::Vector2f target);
    void setAngle(float angle);

	virtual void hit(unsigned int _hp);
	virtual void destroy();
	
    bool exist = true;

    virtual void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);
    Sprite representation;
protected:
    unsigned int hp = 1;
    unsigned int fullHP = hp;
	sf::Vector2f velocity;
    float maxVelocity = 2000;
	
	sf::Vector2f resultantForce;
	
    float mass = 1;
	
    float deltaAngle = 270;
    float angle = 0;
	
private:
	sf::Vector2f oldPosition; //position before last updatePosition
	
    friend class GameplayState;
};
