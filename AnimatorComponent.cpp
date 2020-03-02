#include "main.h"

AnimatorComponent::AnimatorComponent(int _animationStart, int _animationEnd, int _currentFrame, float _animationScale, bool _forwardAndReverse)
{
	animationStart = _animationStart;
	animationEnd = _animationEnd;
	animationScale = _animationScale;
	animationForward = true;
	currentFrame = _currentFrame;
	parent = NULL;
	forwardAndReverse = _forwardAndReverse;
	time = Clock.now();
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
	auto t1 = time;
	auto t2 = Clock.now();

	auto dT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	Tile** world = engine->getMap()->getWorld();
	if (dT >= animationScale * 10)
	{
		time = t2;
		if (animationForward)
		{
			parent->setSprite(currentFrame);
			currentFrame++;
			if (currentFrame >= animationEnd)
			{
				if (forwardAndReverse)
					animationForward = false;
				else currentFrame = animationStart;
			}
		}
		else if (!animationForward)
		{
			parent->setSprite(currentFrame);
			currentFrame--;
			if (currentFrame <= animationStart)
			{
				animationForward = true;
			}
		}
	}
}

bool AnimatorComponent::getAnimationForward() { return animationForward; }
void AnimatorComponent::setAnimationForward(bool _animationForward) { animationForward = _animationForward; }

std::chrono::steady_clock::time_point AnimatorComponent::getTime() { return time; }
void AnimatorComponent::setTime(std::chrono::steady_clock::time_point _time) { time = _time; }