#include "animSprite.h"

AnimatedSprite::AnimatedSprite(AnimationData* data, uint32_t level) 
	:currentFrameX(0), currentFrameY(0),
	currentFrameDuration(sf::seconds(0)),
	currentFrame(1), level(level)
{
	currentAnimation = data->name; 
	animations[currentAnimation] = data;
	animate = data->isAnimation ? true : false;


	//set texture and first frame
	sprite.setTexture(*animations[currentAnimation]->atlas);
	uint32_t left	= animations[currentAnimation]->left;
	uint32_t top	= animations[currentAnimation]->top;
	uint32_t width	= animations[currentAnimation]->width;
	uint32_t height	= animations[currentAnimation]->height;
	sprite.setTextureRect( sf::IntRect(left, top, width, height) );
}


void AnimatedSprite::prepareToDraw(sf::Time elapsedTime) //elapsedTime = elapsedTime from last drawing
{
	//object isn't animation, so this func have nothing to do
	if(!animations[currentAnimation]->isAnimation)	
		return;		

	if(animate)
	{
		calculateFrame(elapsedTime);

		//set cords of next frame
		int x = animations[currentAnimation]->left + 
			currentFrameX*animations[currentAnimation]->width;

		int y = animations[currentAnimation]->top + 
			currentFrameY*animations[currentAnimation]->height;

		int width = animations[currentAnimation]->width;
		int height = animations[currentAnimation]->height;

		//set next frame
		sprite.setTextureRect(sf::IntRect(x, y, width, height));
	}
}


void AnimatedSprite::calculateFrame(sf::Time elapsedTime)
{
	currentFrameDuration += elapsedTime;
	
	uint32_t rowElements = (uint32_t)floor(
						animations[currentAnimation]->atlas->getSize().x /
						animations[currentAnimation]->width);

	//check if animation was finished
	if (currentFrame == animations[currentAnimation]->framesCount) 
	{
		if (animations[currentAnimation]->isLooped) 
			currentFrameX = currentFrameY = 0, currentFrame = 1;
		else	
			animate = false;	
		return;
	}

	// go to next frame if frame_duration_time was reached
	if (currentFrameDuration.asSeconds() >= 
		animations[currentAnimation]->frameDurationTime) 
	{
		//end of line(in atlas)
		if(currentFrameX+1 == rowElements )
		{ 
			currentFrameY++;
			currentFrameX = 0;
		} 
		else
			currentFrameX++;

		currentFrame++;
		currentFrameDuration -=
			sf::seconds(animations[currentAnimation]->frameDurationTime);
	}


}

void AnimatedSprite::draw(sf::Time timeSinceLastDraw, sf::RenderWindow* window)
{
	prepareToDraw(timeSinceLastDraw);
	window->draw(sprite);
}

void AnimatedSprite::addAnimation(AnimationData* animation)
{
	animations[animation->name] = animation; 
}

void AnimatedSprite::removeAnimation(const std::string& name)
{
	animations.erase(name);
}

void AnimatedSprite::setAnimation(const std::string& name)
{
	currentAnimation = name;
	currentFrame = 1;
	currentFrameDuration = sf::seconds(0.0f);
	currentFrameX = currentFrameY = 0;
}

AnimationData* AnimatedSprite::getCurrentAnimation()
{ 
    return animations[currentAnimation]; 
}