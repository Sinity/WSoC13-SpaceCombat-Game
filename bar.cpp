#include "bar.h"

Bar::Bar(float maxValue, sf::Color color, sf::Vector2f size, sf::Vector2f position, int level) :
    Drawable(level), maxValue(maxValue), currentValue(maxValue), color(color), maxWidth(size.x), height(size.y)
{
    representation.setFillColor(color);
    representation.setSize(size);
    representation.setPosition(position);
}


void Bar::draw(sf::Time timeSinceLastDrawing, sf::RenderWindow *window)
{
    auto viewTmp = window->getView();
    window->setView(window->getDefaultView());
    window->draw(representation);
    window->setView(viewTmp);
}

void Bar::update(float currentValue)
{
    float newWidth;

    float curr = currentValue / maxValue;
    newWidth = maxWidth * curr;

    representation.setSize(sf::Vector2f(newWidth, height));
}
