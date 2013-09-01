#pragma once
#include <SFML/Graphics.hpp>

struct TextureRect
{
	TextureRect(){}
	TextureRect(sf::Texture* tex, sf::IntRect position) :
		tex(tex),
		position(position)
	{}
	sf::Texture* tex;
	sf::IntRect position;
};
