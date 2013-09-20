#pragma once

namespace sf {
class RenderWindow;
class Time;
}
class Drawable
{
public:
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual ~Drawable(){}
    Drawable() : level(0){}
    Drawable(int level) : level(level){}

private:
    int level;

    friend class Renderer;
};
