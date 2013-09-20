#include "render.h"
#include "service_locator.h"

void Renderer::draw()
{
    servLoc.getProfiler()->start("rending");

    window.clear();
    for (auto currentLayer : *drawList)
        for (auto currentObject : currentLayer)
            currentObject->draw(&window);
    window.display();

    servLoc.getProfiler()->stop();
}

void Renderer::init(const char* winTitle, uint32_t resX, uint32_t resY)
{
    //if resolution was not specified, window will be fullscreen
    if (resX == 0 || resY == 0)
        window.create(sf::VideoMode::getFullscreenModes()[0],
                winTitle, sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(resX, resY, 32), winTitle);
}

sf::Vector2u Renderer::getResoultion()
{
    return window.getSize();
}

void Renderer::addObj(Drawable* obj)
{
    uint32_t level = obj->level;
    while(drawList->size() <= level)
    {
        drawList->push_back(std::vector<Drawable*>());
    }
    (*drawList)[level].push_back(obj);
}

bool Renderer::removeObj(Drawable* obj)
{
    for (uint32_t i = 0; i < drawList->size(); i++)
        for (uint32_t j = 0; j < (*drawList)[i].size(); j++)
            if ((*drawList)[i][j] == obj)
            {
                (*drawList)[i][j] = (*drawList)[i].back();
                (*drawList)[i].pop_back();
                return true;
            }
    return false;
}

void Renderer::clearList()
{
    drawList->clear();
}

sf::RenderWindow* Renderer::getWindow()
{
    return &window;
}

void Renderer::setDrawList(std::vector<std::vector<Drawable*>>* drawlist)
{
    this->drawList = drawlist;
}
