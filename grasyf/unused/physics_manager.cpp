#include "physics_manager.h"
#include "collision.h"
#include "service_locator.h"

inline void PhysicsManager::detectCollisions()
{
    servLoc.getProfiler()->start("detect collisions");
    for(auto physicalObj : *physicalObjects)
        for(auto with : *physicalObjects)
            if(physicalObj != with && Collision::PixelPerfectTest(physicalObj->getSFMLSprite(), with->getSFMLSprite()))
            {
                if(with->collidingObject == nullptr && physicalObj->collidingObject == nullptr)
                {
                    collisions.push_back(with);
                    collisions.push_back(physicalObj);
                    physicalObj->collidingObject = with;
                    with->collidingObject = physicalObj;
                }
            }
    servLoc.getProfiler()->stop();
}

inline void PhysicsManager::updatePositions(sf::Time elapsedTime)
{
    servLoc.getProfiler()->start("update positions");
    for(auto physicalObj : *physicalObjects)
        physicalObj->updatePosition(elapsedTime);
    servLoc.getProfiler()->stop();
}

inline void PhysicsManager::handleCollisions()
{
    servLoc.getProfiler()->start("resolving collisions");

    for(auto colliding : collisions)
        colliding->onCollision();
    for(auto colliding : collisions)
    {
        colliding->velocity = colliding->newVelocity;
        colliding->collidingObject = nullptr;
    }
    collisions.clear();

    servLoc.getProfiler()->stop();
}

inline void PhysicsManager::cleanForces()
{
    for(auto physicalObj : *physicalObjects)
        physicalObj->resultantForce = {0.f, 0.f};
}

void PhysicsManager::update(sf::Time elapsedTime)
{
    servLoc.getProfiler()->start("physics");

    updatePositions(elapsedTime);
    detectCollisions();
    handleCollisions();
    cleanForces();

    servLoc.getProfiler()->stop();
}

void PhysicsManager::addObj(GameObject* obj)
{
	physicalObjects->push_back(obj);
}

bool PhysicsManager::removeObj(GameObject* obj)
{
	for(unsigned int i = 0; i < physicalObjects->size(); i++)
		if((*physicalObjects)[i] == obj)
		{
			(*physicalObjects)[i] = physicalObjects->back();
			physicalObjects->pop_back();
			return true;
		}
    return false;
}

void PhysicsManager::clearList()
{
    physicalObjects->clear();
}
