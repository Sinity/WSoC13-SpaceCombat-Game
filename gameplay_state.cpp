#include "gameplay_state.h"
#include "estring.h"
#include "service_locator.h"
#include "collision.h"
#include "level.h"
#include "ingamemenustate.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "bullet.h"
#include "portal.h"

GameplayState::GameplayState()
{
    background = new Sprite(servLoc.getResourceManager()->getTextureRect("background"), {0, 0}, 0);
    player = new Player(servLoc.getResourceManager()->getTextureRect("ship"), {0, 0});
    setLevel(1);
    servLoc.getLogger()->log(POS, "Gameplay state initialized");
}

void GameplayState::update(sf::Time elapsedTime)
{
    servLoc.getProfiler()->start("GameplayState: update");

    //physics
    updateObjects(elapsedTime);
    resolveCollisions();
    cleanForces();

    if(!player->exist)
    {//                  TODO SWITCH TO GAMEOVER STATE HERE
        servLoc.getLogger()->log(POS, "Player doesn't exist(destroyed?).");
        servLoc.getEngine()->popState();
        return;
    }

    sf::View view(player->representation.getPosition(), servLoc.getRender()->getWindow()->getDefaultView().getSize());
    servLoc.getRender()->getWindow()->setView(view);

    servLoc.getProfiler()->stop();
}

void GameplayState::setLevel(unsigned int levelID)
{
    //dont draw elements of old level
    if(currentLevel != nullptr)
    {
        for(Enemy* e : currentLevel->enemies)
            servLoc.getRender()->removeObj(&e->representation);
        for(Portal* p : currentLevel->portals)
            servLoc.getRender()->removeObj(&p->representation);
    }
    //check if file is alredy loaded
    for(Level* level : levels)
        if(level->id == levelID)
        {
            currentLevel = level;

            //restore objects
            for(Enemy* e : currentLevel->enemies)
                servLoc.getRender()->addObj(&e->representation);

            for(Portal* p : currentLevel->portals)
                servLoc.getRender()->addObj(&p->representation);

            player->representation.setPosition(currentLevel->startPos);
            return;
        }

    //load from file
    Level* newLevel = new Level;
    newLevel->loadFromFile(ezo::string::format("levels/%u.txt", levelID).c());
    levels.emplace_back(newLevel);
    currentLevel = newLevel;

    player->representation.setPosition(currentLevel->startPos);
}

void GameplayState::updateObjects(sf::Time elapsedTime)
{
    player->update(elapsedTime);
    for(Enemy* enemy : currentLevel->enemies)
        enemy->update(elapsedTime);
}

void GameplayState::resolveCollisions()
{
    //player, portal -> change level
    for(auto portal : currentLevel->portals)
        if(Collision::PixelPerfectTest(player->representation.getSFMLSprite(), portal->representation.getSFMLSprite()))
            setLevel(portal->destinationID);

    //player bullet, enemy -> hit enemy, destroy bullet
    for(auto playerBullet : player->gun->bullets)
        for(Enemy* enemy : currentLevel->enemies)
            if(Collision::PixelPerfectTest(playerBullet->representation.getSFMLSprite(), enemy->representation.getSFMLSprite()))
            {
                enemy->hit(playerBullet->attack);
                playerBullet->destroy();

                //enemy->setPosition(enemy->oldPosition); TODO set small mass  in bullet and enable it.
                //todo: implement better solution(using good equation(this including mass))
                //enemy->velocity = playerBullet->velocity; //bounce from colliding object
            }

    //enemies bullets, player -> hit player
    for(auto enemy : currentLevel->enemies)
        for(auto enemyBullet : enemy->gun->bullets)
            if(Collision::PixelPerfectTest(enemyBullet->representation.getSFMLSprite(), player->representation.getSFMLSprite()))
            {
                player->hit(enemyBullet->attack);
                enemyBullet->destroy();
            }

    //enemy, player -> bounce
    for(Enemy* enemy : currentLevel->enemies)
            if(Collision::PixelPerfectTest(player->representation.getSFMLSprite(), enemy->representation.getSFMLSprite()))
            {
                enemy->representation.setPosition(enemy->oldPosition);
                //todo: implement better solution(using good equation(this including mass))
                sf::Vector2f tempVel = enemy->velocity;
                enemy->velocity = player->velocity; //bounce from colliding object

                player->representation.setPosition(player->oldPosition);
                //todo: implement better solution(using good equation(this including mass))
                player->velocity = tempVel; //bounce from colliding object

                break;
            }

    //enemy, enemy -> bounce
    for(Enemy* enemy1 : currentLevel->enemies)
        for(Enemy* enemy2 : currentLevel->enemies)
            if(enemy1 != enemy2 && Collision::PixelPerfectTest(enemy1->representation.getSFMLSprite(), enemy2->representation.getSFMLSprite()))
            {
                enemy1->representation.setPosition(enemy1->oldPosition);
                //todo: implement better solution(using good equation(this including mass))
                sf::Vector2f tempVel = enemy1->velocity;
                enemy1->velocity = enemy2->velocity; //bounce from colliding object

                enemy2->representation.setPosition(enemy2->oldPosition);
                //todo: implement better solution(using good equation(this including mass))
                enemy2->velocity = tempVel; //bounce from colliding object
            }

}

void GameplayState::cleanForces()
{
    player->resultantForce = {0.f, 0.f};
    for(auto playerBullet : player->gun->bullets)
        playerBullet-> resultantForce = {0.f, 0.f};

    for(Enemy* enemy : currentLevel->enemies)
        enemy->resultantForce = {0.f, 0.f};

    //delete destroyed objects
    for(unsigned int i = 0; i < currentLevel->enemies.size(); i++)
        if(!currentLevel->enemies[i]->exist)
        {
            delete currentLevel->enemies[i];
            currentLevel->enemies.erase(currentLevel->enemies.begin()+i);
        }
}

void GameplayState::handleInput(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
        if(event.key.code == sf::Keyboard::Escape)
            servLoc.getEngine()->pushState(new IngameMenuState());
}

GameplayState::~GameplayState()
{
    delete background;
    delete player;
    for(auto level : levels)
        delete level;
    servLoc.getLogger()->log(POS, "Gameplay state destroyed");
}
