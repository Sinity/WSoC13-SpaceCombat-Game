#pragma once
#include "game_state.h"

class Player;
class Level;
class Sprite;
class GameplayState : public GameState
{
public:
    GameplayState();
    ~GameplayState();

    void handleInput(sf::Event event);
    void update(sf::Time elapsedTime);
	
    void setLevel(unsigned int levelID);

    Player* player = nullptr;

private:
    void updateObjects(sf::Time elapsedTime);
    void resolveCollisions();
    void cleanForces();

	Sprite* background = nullptr;

    std::vector<Level*> levels;
    Level* currentLevel = nullptr;
};

