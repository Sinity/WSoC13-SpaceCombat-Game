#include "ship.h"
#include "service_locator.h"
#include "emath.h"

Ship::Ship(sf::Vector2f position, unsigned int hp, unsigned int radarRadious, unsigned int weaponRadious, unsigned int attack, unsigned int rateOfFire, float mass,
           unsigned int speed) :
    Enemy(servLoc.getResourceManager()->getTextureRect("ship"), position, attack, rateOfFire, weaponRadious, 6666, speed, mass, hp),
    radarRadious(radarRadious), weaponRadious(weaponRadious)
{
    this->hp = hp;
    this->fullHP = hp;
}

void Ship::updateAI()
{
    Enemy::updateAI();

    sf::Vector2f targetVec = target - representation.getPosition();
    float targetVecLen = ezo::vecLength(targetVec.x, targetVec.y);

    switch(state)
    {
    case State::stay:
        if(targetVecLen < radarRadious)
        {
            if(hp < fullHP/2)
                state = State::escape;
            else if(targetVecLen < weaponRadious)
                state = State::fire;
            else
                state = State::chase;
        }
        else
            steeringMode = SteeringMode::Stay;
        break;
    case State::escape:
        if(targetVecLen > radarRadious)
            state = State::stay;
        steeringMode = SteeringMode::Flee;
        break;
    case State::chase:
        if(targetVecLen > radarRadious)
            state = State::stay;
        else if(hp < fullHP/2)
            state = State::escape;
        else if(targetVecLen < weaponRadious)
            state = State::fire;
        else
            steeringMode = SteeringMode::Seek;
        break;
    case State::fire:
        if(targetVecLen > radarRadious)
            state = State::stay;
        else if(hp < fullHP/2)
            state = State::escape;
        else if(targetVecLen > weaponRadious / 3)
            state = State::chase;
        else
            steeringMode = SteeringMode::Stay;
            fire();
        break;
    }
}
