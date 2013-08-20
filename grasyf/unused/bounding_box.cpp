#include "bounding_box.h"


bool BoundingBox::collides(const BoundingBox& box)
{
	if(right < box.left || left > box.right || top > box.bottom || bottom < box.top)
		return false;
	return true;
}


BoundingBox::BoundingBox(const sf::FloatRect& size, sf::Color color)
{
	update(size);
	setColor(color);
}

void BoundingBox::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window)
{
	window->draw(representation);
}

void BoundingBox::setColor(sf::Color color)
{
	this->color = color;
	representation.setFillColor(color);
}

void BoundingBox::update(const sf::FloatRect& size)
{
	width = size.width;
	height = size.height;
	
	left = size.left;
	right = left + width;
	top = size.top;
	bottom = top + height;
	
	representation.setSize( {width, height} );
	representation.setPosition( {left, top} );
}
