#pragma once
#include <vector>

namespace sf {
class Event;
class Time;
}
class Drawable;
class GameState
{
protected:
    std::vector<std::vector<Drawable*>> drawList;

public:
    virtual void handleInput(sf::Event event) = 0;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void resume(){}

    virtual ~GameState(){}
    GameState();

    friend class Game;
};
