#pragma once
#include <SFML/Graphics.hpp>
#include "drawable.h"

class TextureRect;
class Sprite : public Drawable
{
public:
    Sprite(sf::Texture* tex, sf::Vector2f position, int level = 0);
    Sprite(TextureRect texrect, sf::Vector2f position, int level = 0);
    ~Sprite();
    virtual void draw(sf::RenderWindow* window) override;

    //position, size
    virtual void setPosition(const sf::Vector2f& pos);
    virtual sf::Vector2f getPosition() const;
    sf::FloatRect getLocalBounds();

    //transformations
    void setScale(float factorX, float factorY);
    void setOrigin(float x, float y);
    sf::Vector2f getOrigin();
    void setRotation(float angle);

    //for collisions
    const sf::Sprite& getSFMLSprite() { return sprite; }

private:
    sf::Sprite sprite;
};
