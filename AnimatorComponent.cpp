#include "main.h"

AnimatorComponent::AnimatorComponent(int _animationStart, int _animationEnd, float _animationScale)
{
	animationStart = _animationStart;
	animationEnd = _animationEnd;
	animationScale = _animationScale;
	animationForward = true;
	currentFrame = animationStart;
	parent = NULL;
}

AnimatorComponent::~AnimatorComponent()
{

}

int AnimatorComponent::getAnimationStart() { return animationStart; }
void AnimatorComponent::setAnimationStart(int _animationStart) { animationStart = _animationStart; }

int AnimatorComponent::getAnimationEnd() { return animationEnd; }
void AnimatorComponent::setAnimationEnd(int _animationEnd) { animationEnd = _animationEnd; }

int AnimatorComponent::getAnimationScale() { return animationScale; }
void AnimatorComponent::setAnimationScale(int _animationScale) { animationScale = _animationScale; }

Entity* AnimatorComponent::getParent() { return parent; }
void AnimatorComponent::setParent(Entity* _parent) { parent = _parent; }

void AnimatorComponent::animateCellOnTimer()
{
	auto t1 = engine->getTime();
	auto t2 = engine->Clock.now();

	auto dT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	Tile** world = engine->getMap()->getWorld();
	if (dT >= animationScale * 10)
	{
		engine->setTime(t2);
		if (currentFrame <= animationEnd)
		{
			parent->setSprite(currentFrame);
			currentFrame++;
		}
		else if (currentFrame >= animationStart)
		{
			parent->setSprite(currentFrame);
			currentFrame--;
		}
	}
}

bool AnimatorComponent::getAnimationForward() { return animationForward; }
void AnimatorComponent::setAnimationForward(bool _animationForward) { animationForward = _animationForward; }