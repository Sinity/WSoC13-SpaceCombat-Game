#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "drawable.h"

class DrawableVector : public Drawable
{
public:
    DrawableVector(sf::Vector2f vector, sf::Vector2f orgin, sf::Color color = sf::Color::Red);
   
    void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);   
	
    void setOrgin(sf::Vector2f org) { orgin = org; }
    
    void x(float x) { vector.x = x; }
    void y(float y) { vector.y = y; } 
private:
    sf::Vector2f vector;
    sf::Vector2f orgin;
    sf::Color color;
};
