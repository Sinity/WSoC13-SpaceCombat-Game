#include "menu_state.h"
#include "service_locator.h"
#include "collision.h"
#include "sprite.h"
#include "gameplay_state.h"

MenuState::MenuState()
{
    background = new Sprite(servLoc.getResourceManager()->getTextureRect("background"), {0, 0});

    menu_start = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_start"), {100, 100});
    menu_highscores = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_highscores"), {100, 289});
    menu_quit = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_quit"), {100, 478});

    servLoc.getLogger()->log(POS, "Menu state initialized.");
}

MenuState::~MenuState()
{
    delete background;

    delete menu_start;
    delete menu_highscores;
    delete menu_quit;

    servLoc.getLogger()->log(POS, "Menu state destroyed.");
}

void MenuState::handleInput(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

            if(Collision::PixelPerfectTest((menu_start->getSFMLSprite()), mousePos))
                servLoc.getEngine()->pushState(new GameplayState());
            if(Collision::PixelPerfectTest((menu_highscores->getSFMLSprite()), mousePos))
                servLoc.getLogger()->log(POS, "Highscores not implemented yet!");
            if(Collision::PixelPerfectTest((menu_quit->getSFMLSprite()), mousePos))
                servLoc.getEngine()->popState();
        }
    default:
        break;
    }
}

void MenuState::update(sf::Time elapsedTime)
{
}

void MenuState::resume()
{
    servLoc.getRender()->getWindow()->setView(servLoc.getRender()->getWindow()->getDefaultView());
}


