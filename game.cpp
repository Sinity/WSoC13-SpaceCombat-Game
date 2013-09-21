#include "game.h"
#include "service_locator.h"
#include "ezolib.h"
#include "profiler.h"

#include "game_state.h"
#include "menu_state.h"

Game::Game()
{
    srand(time(0));

    servLoc.setEngine(this);
    servLoc.setLogger(&logger);
    servLoc.setProfiler(&profiler);
    servLoc.setRender(&renderer);
    servLoc.setResourceManager(&resourceManager);

    resourceManager.loadResources("resources/resources.txt");

    renderer.init("Space Combat", 1280, 720);
    timeStep = sf::milliseconds(1000 / 60);

    pushState(new MenuState);

    servLoc.getLogger()->log(POS, ezo::string::format(
                                 "App initialized by: Time Step(in milliseconds)->%d(FPS == %d), resolution->%dx%d.",
                                 timeStep.asMilliseconds(), 1000 / timeStep.asMilliseconds(),
                                 servLoc.getRender()->getResoultion().x,
                                 servLoc.getRender()->getResoultion().y).c());
}

void Game::run()
{
    sf::Clock mainTimer, fpsTimer;
    sf::Time accumulatedTime, lastAccumulatedTime, elapsedTime;
    const int fpsFrequency = 1000; //intervals between refreshing fps value in miliseconds
    unsigned int framesCount = 0; //frames since last fps refresh

    Logger fpsLog("logz/fps");
    fpsLog.setBufferSize(300);

    while(!states.empty())
    {
        profiler.start("game loop");

        elapsedTime = std::max(sf::microseconds(0), mainTimer.restart()); //get delta time and make sure it is >= 0
        accumulatedTime += elapsedTime;
        accumulatedTime = sf::seconds(ezo::clamp(accumulatedTime.asSeconds(), 0.f, 1.f)); //make sure that accumulated time is not too big
        lastAccumulatedTime = accumulatedTime;

        framesCount++;
        if(fpsTimer.getElapsedTime().asMilliseconds() > fpsFrequency)
        {
            unsigned int fps = framesCount * 1000.f/fpsFrequency;
            fpsLog.log(POS, ezo::string::format("FPS: %d", fps).c(), LogType::Information, LogOutput::TxtFileAndConsole);
            fpsTimer.restart();
            framesCount = 0;
        }

        //Game will be fully independient of real time(each loop == exactly time step) if uncommented. Useful for debugging purposes.
             //accumulatedTime = timeStep;

        for(; accumulatedTime >= timeStep; accumulatedTime -= timeStep)
        {
            handleInput();
            update(timeStep);
        }

        renderer.draw();

        profiler.stop();
    }
}

void Game::handleInput()
{
    static sf::Event currentEvent;
    while(servLoc.getRender()->getWindow()->pollEvent(currentEvent))
    {
        servLoc.getProfiler()->start("event");

        if(currentEvent.type == sf::Event::Closed)
        {
            servLoc.getLogger()->log(POS, "Close request");
            while(!states.empty())
                servLoc.getEngine()->popState();
        }
        else if(!states.empty())
            states.back()->handleInput(currentEvent);

        servLoc.getProfiler()->stop();
    }
}

void Game::update(sf::Time elapsedTime)
{
    profiler.start("update");

    if(!states.empty())
        states.back()->update(elapsedTime);

    profiler.stop();
}

void Game::popState()
{
    delete states.back();
    states.pop_back();

    if(!states.empty())
    {
        renderer.setDrawList(&states.back()->drawList);
        states.back()->resume();
    }
    else
        renderer.setDrawList(new std::vector<std::vector<Drawable*>>);
}

void Game::pushState(GameState* state)
{
    states.push_back(state);
}

Game::~Game()
{
    while(!states.empty())
        popState();
    logger.log(POS, "Game destroyed");
}
