#pragma once
#include "drawable.h"
#include <SFML/Graphics.hpp>

class Bar : public Drawable
{
public:
    Bar(float maxValue, sf::Color color, sf::Vector2f size, sf::Vector2f position, int level = 0);
    void draw(sf::RenderWindow* window);
    void update(float currentValue);

private:
    float maxValue;
    float currentValue;

    sf::Color color;
    sf::RectangleShape representation;
    sf::RectangleShape frame;
    float maxWidth, height;
};
