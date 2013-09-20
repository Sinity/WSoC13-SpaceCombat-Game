#include "text.h"


void Text::draw(sf::RenderWindow *window)
{
    auto viewTmp = window->getView();
    window->setView(window->getDefaultView());
    window->draw(text);
    window->setView(viewTmp);
}
