#include "gun.h"
#include "service_locator.h"
#include "ezolib.h"
#include "bullet.h"

Gun::Gun(const float* baseAngle, float shootsPerSecond, int attack, float range,
         sf::Vector2f differencePosition, unsigned int speed, float differenceAngle) :
    diffPosition(differencePosition), baseAngle(baseAngle), diffAngle(differenceAngle),
    haltDuration(sf::seconds(1 / shootsPerSecond)), attack(attack), speed(speed), range(range)

{

}

Gun::~Gun()
{
    for(auto bullet : bullets)
        delete bullet;
}

void Gun::shoot(sf::Vector2f target, sf::Vector2f basePosition)
{
    haltAccumulator += clock.restart();
    if(haltAccumulator > haltDuration)
    {
        sf::Vector2f shootDirection((float)sin(ezo::degToRad(*baseAngle + diffAngle)),
                                    (float)-cos(ezo::degToRad(*baseAngle + diffAngle)));

        Bullet* bullet = new Bullet(servLoc.getResourceManager()->getTextureRect("bullet_green"),
                               sf::Vector2f(basePosition.x + diffPosition.x*shootDirection.x,
                                            basePosition.y + diffPosition.y*shootDirection.y),
                                    shootDirection, range, attack, speed);

        bullet->setAngle(*baseAngle + diffAngle);
        bullets.push_back(bullet);

        haltAccumulator = sf::microseconds(0);
    }
}

void Gun::update(sf::Time elapsedTime)
{
    for(Bullet* bullet : bullets)
        bullet->update(elapsedTime);

    //delate destroyed bullets
    for(unsigned int i = 0; i < bullets.size(); i++)
        if(!bullets[i]->exist)
            delete bullets[i],
            bullets.erase(bullets.begin() + i);
}
