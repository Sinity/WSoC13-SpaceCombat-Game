#pragma once
#include <vector>
#include "game_object.h"

class PhysicsManager : public ezo::Object
{
public:
	void update(sf::Time elapsedTime);

    void addObj(GameObject* obj);
    bool removeObj(GameObject* obj);
    void clearList();

	void setObjectsList(std::vector<GameObject*>* objs) { physicalObjects = objs; }
private:
    void updatePositions(sf::Time elapsedTime);
    void detectCollisions();
    void handleCollisions();
    void cleanForces();

	std::vector<GameObject*>* physicalObjects;
	std::vector<GameObject*> collisions;
};
