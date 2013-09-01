#include "drawablevector.h"
#include "service_locator.h"

DrawableVector::DrawableVector(sf::Vector2f vec, sf::Vector2f org, sf::Color color) :
	vector(vec),
	orgin(org),
	color(color)
{
    servLoc.getRender()->addObj(this);
}

DrawableVector::~DrawableVector()
{
    servLoc.getRender()->addObj(this);
}

void DrawableVector::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window)
{ 
    window->draw(line, 2, sf::Lines);
}
