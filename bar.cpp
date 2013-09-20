#include "bar.h"

Bar::Bar(float maxValue, sf::Color color, sf::Vector2f size, sf::Vector2f position, int level) :
    Drawable(level), maxValue(maxValue), currentValue(maxValue), color(color), maxWidth(size.x), height(size.y)
{
    representation.setFillColor(color);
    representation.setSize(size);
    representation.setPosition(position);

    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(color);
    frame.setOutlineThickness(1);
    frame.setSize(size);
    frame.setPosition(position);
}


void Bar::draw(sf::RenderWindow* window)
{
    auto viewTmp = window->getView();
    window->setView(window->getDefaultView());

    window->draw(representation);
    window->draw(frame);

    window->setView(viewTmp);
}

void Bar::update(float currentValue)
{
    float currentFill = currentValue / maxValue;
    representation.setSize(sf::Vector2f(maxWidth * currentFill, height));
}
