#include "portal.h"
#include "service_locator.h"
#include "gameplay_state.h"
#include "player.h"

Portal::Portal(unsigned int destinationID, sf::Vector2f position) :
    GameObject(servLoc.getResourceManager()->getTextureRect("ship"), position, 1),
    destinationID(destinationID)
{}
