#include "ingamemenustate.h"
#include "service_locator.h"
#include "collision.h"
#include "sprite.h"

IngameMenuState::IngameMenuState()
{
    buttonReturnToGame = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_back"),
                             {
                                 (float)servLoc.getRender()->getWindow()->getSize().x / 2 - servLoc.getResourceManager()->getTextureRect("menu_back").position.width / 2,
                                 (float)servLoc.getResourceManager()->getTextureRect("menu_back").position.height / 2
                             });
    buttonReturnToMainMenu = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_return"),
                            {
                               (float)servLoc.getRender()->getWindow()->getSize().x / 2 - servLoc.getResourceManager()->getTextureRect("menu_return").position.width / 2,
                               (float)servLoc.getRender()->getWindow()->getSize().y / 2 - servLoc.getResourceManager()->getTextureRect("menu_return").position.height / 2
                            });
    buttonQuitGame = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_quit"),
                            {
                               (float)servLoc.getRender()->getWindow()->getSize().x / 2 - servLoc.getResourceManager()->getTextureRect("menu_quit").position.width / 2,
                               (float)servLoc.getRender()->getWindow()->getSize().y - servLoc.getResourceManager()->getTextureRect("menu_quit").position.height
                            });
    servLoc.getRender()->getWindow()->setView(servLoc.getRender()->getWindow()->getDefaultView());
}

IngameMenuState::~IngameMenuState()
{
    delete buttonReturnToMainMenu;
    delete buttonQuitGame;
    delete buttonReturnToGame;
}

void IngameMenuState::handleInput(sf::Event currentEvent)
{
    switch(currentEvent.type)
    {
    case sf::Event::MouseButtonPressed:
        if(currentEvent.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = {currentEvent.mouseButton.x, currentEvent.mouseButton.y};

            if(Collision::PixelPerfectTest((buttonReturnToGame->getSFMLSprite()), mousePos))
                returnToGame = true;
            else if(Collision::PixelPerfectTest((buttonReturnToMainMenu->getSFMLSprite()), mousePos))
                returnToMainMenu = true;
            else if(Collision::PixelPerfectTest((buttonQuitGame->getSFMLSprite()), mousePos))
                quitGame = true;
        }
        break;

    case sf::Event::KeyPressed:
        if(currentEvent.key.code == sf::Keyboard::Escape)
            returnToGame = true;
        break;

    default:
        break;
    }
}

void IngameMenuState::update(sf::Time elapsedTime)
{
    if(returnToGame)
        servLoc.getEngine()->popState();
    else if(returnToMainMenu)
    {
        servLoc.getEngine()->popState();
        servLoc.getEngine()->popState();
    }
    else if(quitGame)
    {
        servLoc.getEngine()->popState();
        servLoc.getEngine()->popState();
        servLoc.getEngine()->popState();
    }
}
