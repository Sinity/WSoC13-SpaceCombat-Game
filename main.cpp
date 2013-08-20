#include "game.h"
#include "service_locator.h"

ServiceLocator servLoc;
int main()
{
    //Initialize game
    Game game;

	//Run main loop
    game.run();

	return EXIT_SUCCESS;
}

