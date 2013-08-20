#include "drawablevector.h"

DrawableVector::DrawableVector(sf::Vector2f vec, sf::Vector2f org, sf::Color color) :
	vector(vec),
	orgin(org),
	color(color)
{
}

void DrawableVector::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window)
{ 
    sf::Vertex line[] =
    {
		sf::Vertex(sf::Vector2f(orgin.x, orgin.y), this->color),
		sf::Vertex(sf::Vector2f(vector.x, vector.y), this->color)
    };
    window->draw(line, 2, sf::Lines);
}
