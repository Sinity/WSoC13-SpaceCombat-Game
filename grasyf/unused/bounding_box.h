#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "drawable.h" // Base class: Drawable
#include "SFML\Graphics.hpp"

class BoundingBox : public Drawable
{
public:
	BoundingBox(const sf::FloatRect& size, sf::Color = {0, 0, 255, 0.5 * 255} );
	void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);
	bool collides(const BoundingBox& box);
	void update(const sf::FloatRect& size);
	
	void setColor(sf::Color color);
	
private:
	float left, top, bottom, right; //position
	float width, height;			//dimmenstions
	sf::Color color;

	sf::RectangleShape representation;
};

#endif // BOUNDINGBOX_H
