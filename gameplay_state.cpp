#include "gameplay_state.h"
#include "estring.h"
#include "emath.h"
#include "service_locator.h"
#include "collision.h"
#include "ingamemenustate.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "bullet.h"
#include "bar.h"
#include "text.h"
#include "ship.h"

GameplayState::GameplayState()
{
    player = new Player(servLoc.getResourceManager()->getTextureRect("ship"), {0, 0});

    playerHP = new Bar(player->hp, sf::Color::Red, {600, 30}, {0, 0});
    servLoc.getRender()->addObj(playerHP);

    score = new Text;
    servLoc.getRender()->addObj(score);
    score->font.loadFromFile("resources/arial.ttf");
    score->text.setFont(score->font);
    score->text.setPosition({0, 35});
    score->text.setColor(sf::Color::Green);

    player->representation.setPosition({0.f, 0.f});
    enemies.push_back(new Ship({700.f, 700.f}, 20, 1500, 650, 1, 6.f, 10000.f, 100000000));

    servLoc.getLogger()->log(POS, "Gameplay state initialized");
}

void GameplayState::update(sf::Time elapsedTime)
{
    servLoc.getProfiler()->start("GameplayState: update");

    //physics
    updateObjects(elapsedTime);
    resolveCollisions();
    cleanForces();
    resolveExistance();

    if(!player->exist)
    {
        servLoc.getLogger()->log(POS, "Player doesn't exist(destroyed).");
        servLoc.getEngine()->popState();
        return;
    }

    playerHP->update(player->hp);
    score->text.setString(ezo::string::format("Score: %u", player->score).c());

    servLoc.getRender()->getWindow()->setView(sf::View(player->representation.getPosition(),
                                                       servLoc.getRender()->getWindow()->getDefaultView().getSize()));

    servLoc.getProfiler()->stop();
}

void GameplayState::updateObjects(sf::Time elapsedTime)
{
    player->update(elapsedTime);
    for(Enemy* enemy :  enemies)
        enemy->update(elapsedTime);
}

void GameplayState::resolveCollisions()
{
    servLoc.getProfiler()->start("collisions");

    servLoc.getProfiler()->start("pbullet, enemy");
    //player bullet, enemy -> hit enemy, destroy bullet
    for(auto playerBullet : player->gun->bullets)
        for(Enemy* enemy :  enemies)
            if(Collision::PixelPerfectTest(playerBullet->representation.getSFMLSprite(), enemy->representation.getSFMLSprite()))
            {
                enemy->hit(playerBullet->attack);
                playerBullet->destroy();

                if(!enemy->exist)
                    player->score++;
            }
    servLoc.getProfiler()->stop();


    servLoc.getProfiler()->start("ebullet, player");
    //enemies bullets, player -> hit player
    for(auto enemy :  enemies)
        for(auto enemyBullet : enemy->gun->bullets)
            if(Collision::PixelPerfectTest(enemyBullet->representation.getSFMLSprite(), player->representation.getSFMLSprite()))
            {
                player->hit(enemyBullet->attack);
                enemyBullet->destroy();
            }
    servLoc.getProfiler()->stop();

    servLoc.getProfiler()->start("enemy, player");
    //enemy, player -> bounce
    for(Enemy* enemy :  enemies)
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
    servLoc.getProfiler()->stop();

    servLoc.getProfiler()->start("enemy, enemy");
    //enemy, enemy -> bounce
    for(Enemy* enemy1 :  enemies)
        for(Enemy* enemy2 :  enemies)
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
    servLoc.getProfiler()->stop();

    servLoc.getProfiler()->stop();
}

void GameplayState::cleanForces()
{
    player->resultantForce = {0.f, 0.f};
    for(auto playerBullet : player->gun->bullets)
        playerBullet-> resultantForce = {0.f, 0.f};

    for(Enemy* enemy :  enemies)
        enemy->resultantForce = {0.f, 0.f};
}

void GameplayState::resolveExistance()
{
    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        sf::Vector2f playerPos = player->representation.getPosition();
        float enemyLen = ezo::vecLength(playerPos.x -  enemies[i]->representation.getPosition().x,
                                        playerPos.y -  enemies[i]->representation.getPosition().y);
        if(enemyLen > 2000.f)
        {
            std::uniform_real_distribution<float> dist(700, 900);
            sf::Vector2f playerPos = player->representation.getPosition();
            enemies[i]->representation.setPosition({playerPos.x + dist(randEngine), playerPos.y + dist(randEngine)});
        }
        if(!enemies[i]->exist)
        {
            std::uniform_real_distribution<float> dist(700, 800);
            std::uniform_int_distribution<int> boolDist(false, true);

            if(boolDist(randEngine))
            {
                player->hp += enemies[i]->attack;
                if(player->hp > player->fullHP)
                    player->hp = player->fullHP;
            }

            delete enemies[i];
            enemies.erase( enemies.begin() + i);

            static unsigned int enemyHP, enemyAttack;

            unsigned int enemiesCount;
            if(player->score < 3)
                enemiesCount = 1,
                enemyHP = 30,
                enemyAttack = 1;
            else if(player->score < 10)
                enemiesCount = 2,
                enemyHP = 60,
                enemyAttack = 2;
            else if(player->score < 50)
                enemiesCount = 4,
                enemyHP = 80,
                enemyAttack = 3;
            else if(player->score < 100)
                enemiesCount = 7,
                enemyHP = 100,
                enemyAttack = 5;
            else if(player->score < 200)
                enemiesCount = 10,
                enemyHP = 150,
                enemyAttack = 4;
            else if(player->score < 1000)
                enemiesCount = 12,
                enemyHP = 180,
                enemyAttack = 5;
            else
                enemiesCount = 17,
                enemyHP = 200,
                enemyAttack = 8;

            for(unsigned int i = enemies.size(); i < enemiesCount; i++)
            {
                sf::Vector2f enemyPos;
                float xpart = dist(randEngine);
                float ypart = dist(randEngine);
                if(boolDist(randEngine))    xpart = -xpart;
                if(boolDist(randEngine))    ypart = -ypart;
                enemyPos.x = xpart + player->representation.getPosition().x;
                enemyPos.y = ypart + player->representation.getPosition().y;

                enemies.push_back(new Ship(enemyPos, enemyHP, 1100, 700, enemyAttack, 6, 10000, 100000000));
            }
        }
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
    delete player;
    delete playerHP;
    delete score;
    for(auto enemy : enemies)
        delete enemy;
    servLoc.getLogger()->log(POS, "Gameplay state destroyed");
}
