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
	
    void setOrgin(sf::Vector2f org) { orgin = org; updateRepr();}
    void setColor(sf::Color color) { this->color = color; updateRepr();}
    void x(float x) { vector.x = x; updateRepr();}
    void y(float y) { vector.y = y; updateRepr();}
    void xy(sf::Vector2f xy) { vector = xy; updateRepr();}
private:
    sf::Vector2f vector;
    sf::Vector2f orgin;
    sf::Color color;
    sf::Vertex line[2];
    void updateRepr()
    {
        line[0] =  sf::Vertex(sf::Vector2f(orgin.x, orgin.y), this->color);
        line[1] =  sf::Vertex(sf::Vector2f(vector.x, vector.y), this->color);
    }
};
