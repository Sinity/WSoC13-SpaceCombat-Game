#include "ship.h"
#include "service_locator.h"
#include "emath.h"

Ship::Ship(sf::Vector2f position, Player* player, unsigned int hp, unsigned int attack,
           unsigned int radarRadious, unsigned int weaponRadious) :
    Enemy(servLoc.getResourceManager()->getTextureRect("ship"), position, player),
    radarRadious(radarRadious),
    weaponRadious(weaponRadious)
{
    this->hp = hp;
    this->fullHP = hp;
    this->attack = attack;
}

/*
 *     if can see player
          if hp < 50%
               if rand(1, 100-hp) > 50
                  escape()
           else if can hit player ( range of weapon is sufficient )
                activateGun()
           else
                chase()
         else
               stay()
*/

void Ship::updateAI(sf::Time elapsedTime, Player *player)
{
    Enemy::updateAI(elapsedTime, player);

    /*sf::Vector2f playerVec = player->getPosition() - this->getPosition();
    unsigned int playerVecLength = (int)ezo::vecLength(playerVec.x, playerVec.y);

    switch(state)
    {
    case stay:
        if(radarRadious > playerVecLength)
        {
            if(hp < fullHP / 2)
            {
                if(rand()%(100-hp) > 50)
                    state = escape;
            }
            else if(weaponRadious > playerVecLength)
                state = shoot;
            else
                state = chase;

        }
        else
        {
            afterburnerActive = false;
        }
        break;
    case escape:
        if(radarRadious < playerVecLength)
            state = stay;
        else
        {
            calculateAngle(elapsedTime, -player->getPosition());
            afterburnerActive = true;
        }
        break;
    case shoot:
        if(hp < fullHP / 2)
            state = escape;
        else if(radarRadious < playerVecLength)
            state = stay;
        else
            Enemy::shoot({0, 0});
        break;
    case chase:
        if(radarRadious < playerVecLength)
            state = stay;
        else if(weaponRadious > playerVecLength)
            state = shoot;
        else
            calculateAngle(elapsedTime, player->getPosition());
        break;
    }*/
}
