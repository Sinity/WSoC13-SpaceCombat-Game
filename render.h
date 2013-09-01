#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "drawable.h"

class Renderer
{
public:
	//if resolution was not specified, window will be fullscreen 
	void init(const char* winTitle = "", unsigned int resX = 0, unsigned int resY = 0);
    ~Renderer(){ delete drawList; }
	void draw();

	void addObj(Drawable* obj);
	bool removeObj(Drawable* obj); 
    void clearList();

	void setDrawList(std::vector<std::vector<Drawable*>>* drawlist);
	
	sf::Vector2u getResoultion();
	sf::RenderWindow* getWindow();

private:
	std::vector<std::vector<Drawable*>>* drawList;

	sf::Time timeSinceLastDrawing;
	sf::Clock timer;

	sf::RenderWindow window;
};
