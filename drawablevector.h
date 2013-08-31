#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "drawable.h"

class DrawableVector : public Drawable
{
public:
    DrawableVector(sf::Vector2f vector = {0.f, 0.f}, sf::Vector2f orgin = {0.f, 0.f}, sf::Color color = sf::Color::Red);
    ~DrawableVector();

    void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);   
	
    void setOrgin(sf::Vector2f org) { orgin = org; }
    void setColor(sf::Color color) { this->color = color; }
    void x(float x) { vector.x = x; }
    void y(float y) { vector.y = y; } 
    void xy(sf::Vector2f xy) { vector = xy; }
private:
    sf::Vector2f vector;
    sf::Vector2f orgin;
    sf::Color color;
};
