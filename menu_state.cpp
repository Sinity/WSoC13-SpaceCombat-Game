#include "menu_state.h"
#include "service_locator.h"
#include "collision.h"
#include "sprite.h"
#include "gameplay_state.h"

MenuState::MenuState()
{
    background = new Sprite(servLoc.getResourceManager()->getTextureRect("background"), {0, 0});
    background->setScale(servLoc.getRender()->getWindow()->getSize().x / background->getSFMLSprite().getGlobalBounds().width,
                         servLoc.getRender()->getWindow()->getSize().y / background->getSFMLSprite().getGlobalBounds().height);

    buttonStartGame = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_start"),
                            {
                                (float)servLoc.getRender()->getWindow()->getSize().x / 2 - servLoc.getResourceManager()->getTextureRect("menu_start").position.width / 2,
                                (float)servLoc.getRender()->getWindow()->getSize().y / 2 - servLoc.getResourceManager()->getTextureRect("menu_start").position.height / 2
                            });

    buttonQuitGame = new Sprite(servLoc.getResourceManager()->getTextureRect("menu_quit"),
                            {
                               (float)servLoc.getRender()->getWindow()->getSize().x / 2 - servLoc.getResourceManager()->getTextureRect("menu_quit").position.width / 2,
                               (float)servLoc.getRender()->getWindow()->getSize().y - servLoc.getResourceManager()->getTextureRect("menu_quit").position.height
                            });

    servLoc.getLogger()->log(POS, "Menu state initialized.");
}

MenuState::~MenuState()
{
    delete background;
    delete buttonStartGame;
    delete buttonQuitGame;
    servLoc.getLogger()->log(POS, "Menu state destroyed.");
}

void MenuState::handleInput(sf::Event currentEvent)
{
    switch(currentEvent.type)
    {
    case sf::Event::MouseButtonPressed:
        if(currentEvent.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = {currentEvent.mouseButton.x, currentEvent.mouseButton.y};

            if(Collision::PixelPerfectTest((buttonStartGame->getSFMLSprite()), mousePos))
                startGame = true;
            else if(Collision::PixelPerfectTest((buttonQuitGame->getSFMLSprite()), mousePos))
                quitGame = true;
        }

    default:
        break;
    }
}

void MenuState::update(sf::Time elapsedTime)
{
    if(startGame)
        servLoc.getEngine()->pushState(new GameplayState());
    else if(quitGame)
        servLoc.getEngine()->popState();
}

void MenuState::resume()
{
    servLoc.getRender()->getWindow()->setView(servLoc.getRender()->getWindow()->getDefaultView());
}


