#include "game_state.h"
#include "service_locator.h"

GameState::GameState()
{
    servLoc.getRender()->setDrawList(&drawList);
}
