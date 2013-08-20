#pragma once
#include <string>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "ezolib.h"

struct AnimationData 
{
	std::string name; //name of animation

	uint32_t left;   //offset between fistt frame and left side of texture
	uint32_t top;    //offset between first frame and top of texture
	uint32_t width;  //width of frame in pixels
	uint32_t height; //height of frame in pixels
        
        uint32_t framesCount; //count of frames in animation
	float frameDurationTime; //duration of TODO
               
	bool isAnimation; //have more frames than one?
	bool isLooped;  //if true, after last frame will be the first frame 

	char atlasName[80]; //name of atlas contain this animation
	sf::Texture* atlas; //adress of texture atlas containing this animation
};

class AnimatedSprite
{
public:
	AnimatedSprite(AnimationData* data, uint32_t level = 1);
        AnimatedSprite(){}
        //Select suitable frame and draw object on a specific window
	virtual void draw(sf::Time timeSinceLastDrawing, sf::RenderWindow* window);   
	sf::Sprite* getSprite() { return &sprite; }

	void addAnimation(AnimationData* animation);
	void removeAnimation(const std::string& name);
	void setAnimation(const std::string& name);
	AnimationData* getCurrentAnimation();
		
	uint32_t getLevel() { return level; }
private:
	sf::Sprite sprite;

	void prepareToDraw(sf::Time elapsedTime); //Calculates current frame and sets it
	void calculateFrame(sf::Time elapsedTime);

	std::map<std::string, AnimationData*> animations;
	std::string currentAnimation;

	bool animate;	//if false, this willn't be animated

	size_t currentFrameX; // number of current frame in row(from 0)
	size_t currentFrameY; // number of current row(from 0)
	sf::Time currentFrameDuration;
        size_t currentFrame;   //number of current frame indexed from 1
	uint32_t level;  // plan, na kt�rym b�dzie rysowany sprite. 0 - pierwszy plan
};