#include "ingamemenustate.h"
#include "service_locator.h"
#include "collision.h"
#include "sprite.h"

IngameMenuState::IngameMenuState()
{
    menu_return = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_back"),  {
                                 servLoc.getRender()->getWindow()->getSize().x / 2 -
                                     servLoc.getResourceManager()->getTextureRect("menu_start").position.width / 2,

                                     servLoc.getResourceManager()->getTextureRect("menu_start").position.height / 2
                             }, 1);
    menu_main = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_return"),  {
                               servLoc.getRender()->getWindow()->getSize().x / 2 -
                                   servLoc.getResourceManager()->getTextureRect("menu_start").position.width / 2,

                               servLoc.getRender()->getWindow()->getSize().y / 2 -
                                   servLoc.getResourceManager()->getTextureRect("menu_start").position.height / 2
                           }, 1);
    menu_quit = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_quit"),  {
                               servLoc.getRender()->getWindow()->getSize().x / 2 -
                                   servLoc.getResourceManager()->getTextureRect("menu_start").position.width / 2,

                               servLoc.getRender()->getWindow()->getSize().y -
                                   servLoc.getResourceManager()->getTextureRect("menu_start").position.height
                           }, 1);
    servLoc.getRender()->getWindow()->setView(servLoc.getRender()->getWindow()->getDefaultView());
}

IngameMenuState::~IngameMenuState()
{
    delete menu_main;
    delete menu_quit;
    delete menu_return;
    delete under_menu;
}

void IngameMenuState::handleInput(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

            if(Collision::PixelPerfectTest((menu_return->getSFMLSprite()), mousePos))
            {
                servLoc.getEngine()->popState();
                return;
            }
            if(Collision::PixelPerfectTest((menu_main->getSFMLSprite()), mousePos))
            {
                servLoc.getEngine()->popState();
                servLoc.getEngine()->popState();
                return;
            }
            if(Collision::PixelPerfectTest((menu_quit->getSFMLSprite()), mousePos))
            {
                servLoc.getEngine()->popState();
                servLoc.getEngine()->popState();
                servLoc.getEngine()->popState();
                return;
            }
        }
        break;
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
            servLoc.getEngine()->popState();
        break;
    default:
        break;
    }
}

void IngameMenuState::update(sf::Time elapsedTime)
{
}
