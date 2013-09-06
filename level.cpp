#include "level.h"
#include <fstream>
#include <cstdlib>
#include "service_locator.h"
#include "enemy.h"
#include "ship.h"
#include "gameplay_state.h"
#include "portal.h"

bool Level::loadFromFile(const char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        return false;

    while(file.good())
    {
        std::string type;
        file >> type;
        if(type == "start")
        {
            std::string tmp;
            file >> tmp;
            startPos.x = atoi(tmp.c_str());
            file >> tmp;
            startPos.y = atoi(tmp.c_str());
        }
        else if(type == "id")
        {
            std::string tmp;
            file >> tmp;
            id = atoi(tmp.c_str());
        }
        else if(type == "enemy")
        {
            std::string subtype;
            file >> subtype;
            if(subtype == "ship")
            {
                sf::Vector2f pos;
                unsigned int hp, speed, attack, rateOfFire;
                unsigned int radarRadious, weaponRadious;
                float mass;
                file >> pos.x;
                file >> pos.y;
                file >> hp;
                file >> speed;
                file >> attack;
                file >> rateOfFire;
                file >> radarRadious;
                file >> weaponRadious;
                file >> mass;

                enemies.push_back(new Ship(pos, hp, radarRadious, weaponRadious, attack, rateOfFire, mass, speed));
            }
        }
        else if(type == "portal")
        {
            std::string tmp;
            sf::Vector2f portalPos;
            unsigned int destination;
            file >> tmp;
            destination = atoi(tmp.c_str());
            file >> tmp;
            portalPos.x = atoi(tmp.c_str());
            file >> tmp;
            portalPos.y = atoi(tmp.c_str());

            portals.push_back(new Portal(destination, portalPos));
        }
        else
            return false;
    }

    return true;
}

Level::~Level()
{
    for(auto p : portals)
        delete p;
    for(auto e : enemies)
        delete e;
}
