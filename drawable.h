#pragma once

namespace sf {
class RenderWindow;
class Time;
}
class Drawable
{
public:
    virtual void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window) = 0;
	virtual ~Drawable(){}
	Drawable() : level(0){}
    Drawable(int level) : level(level){}
	
	void setLevel(int level);
	int getLevel() const;
	
private:
	int level;
};
