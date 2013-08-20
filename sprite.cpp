#include "sprite.h"
#include "service_locator.h"
#include "textureRect.h"

Sprite::Sprite(sf::Texture* tex, sf::Vector2f position, int level)
{
	sprite.setTexture(*tex);
	setPosition(position);
	setLevel(level);
	servLoc.getRender()->addObj(this);
}

Sprite::Sprite(TextureRect texrect, sf::Vector2f position, int level)
{
	sprite.setTexture(*texrect.tex);
	if(texrect.position.width != 0 || texrect.position.height != 0)
		sprite.setTextureRect(texrect.position);
	setPosition(position);
	setLevel(level);
    servLoc.getRender()->addObj(this);
}

void Sprite::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window)
{
    servLoc.getProfiler()->start("drawing sprite");
	window->draw(sprite);
    servLoc.getProfiler()->stop();
}

///////////////////////////////
////// WRAPPER FUNCTIONS  /////
///////////////////////////////
sf::Vector2f Sprite::getPosition() const
{
	return sprite.getPosition();
}

void Sprite::setPosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

void Sprite::setScale(float factorX, float factorY)
{
	sprite.setScale(factorX, factorY);
}

sf::FloatRect Sprite::getLocalBounds()
{
	return sprite.getLocalBounds();
}

void Sprite::setOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}

void Sprite::setRotation(float angle)
{
	sprite.setRotation(angle);
}

sf::Vector2f Sprite::getOrigin()
{
	return sprite.getOrigin();
}

Sprite::~Sprite()
{
	servLoc.getRender()->removeObj(this);
}
