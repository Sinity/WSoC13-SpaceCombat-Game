#pragma once
#include "drawable.h"
#include <SFML/Graphics.hpp>

class Text : public Drawable
{
public:
    void draw(sf::RenderWindow* window);

    sf::Text text;
    sf::Font font;
};
