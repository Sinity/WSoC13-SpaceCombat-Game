#ifndef TEXT_H
#define TEXT_H
#include "drawable.h"
#include "SFML/Graphics.hpp"
class Text : public Drawable
{
public:
    void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);

    sf::Text text;
    sf::Font font;
};

#endif // TEXT_H
