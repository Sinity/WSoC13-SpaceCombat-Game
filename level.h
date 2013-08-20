#pragma once
#include <vector>
#include <SFML/System.hpp>

class Portal;
class Enemy;
class Level
{
public:
    ~Level();
    bool loadFromFile(const char* filename);

    unsigned int id = 0;
    std::vector<Enemy*> enemies;
    std::vector<Portal*> portals;
    sf::Vector2f startPos;
};
