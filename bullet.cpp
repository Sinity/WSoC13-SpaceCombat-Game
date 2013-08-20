#include "bullet.h"
#include "textureRect.h"

Bullet::Bullet(TextureRect texrect, sf::Vector2f position, sf::Vector2f direction, float speed, unsigned int attack) :
	GameObject(texrect, position, 1), attack(attack)
{
    representation.setOrigin(representation.getLocalBounds().width / 2, representation.getLocalBounds().height / 2);
    representation.setPosition(position);
	maxVelocity = 2100;
	velocity = { direction.x * speed, direction.y * speed };
}
