#pragma once
#include "logger.h"
#include "render.h"
#include "resource_manager.h"
#include "profiler.h"

class GameState;
class Game
{
public:
    void run(); //Runs main loop
    void handleInput();
    void update(sf::Time elapsedTime);

    void pushState(GameState* state);
    void popState();
    std::vector<GameState*> states;

    Game();
    ~Game();
private:
    sf::Time timeStep; //time for one main loop iteration

    Logger logger;
    Profiler profiler;

    Renderer renderer;
    ResourceManager resourceManager;
};
