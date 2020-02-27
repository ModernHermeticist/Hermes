#pragma once

class Entity;

class AnimatorComponent
{
public:
	AnimatorComponent(int _animationStart, int _animationEnd, float _animationScale);
	~AnimatorComponent();

	int getAnimationStart();
	void setAnimationStart(int _animationStart);

	int getAnimationEnd();
	void setAnimationEnd(int _animationEnd);

	int getAnimationScale();
	void setAnimationScale(int _animationScale);

	Entity* getParent();
	void setParent(Entity* _parent);

	void animateCellOnTimer();

	bool getAnimationForward();
	void setAnimationForward(bool _animationForward);

private:
	int animationStart;
	int animationEnd;
	float animationScale;
	bool animationForward;

	int currentFrame;

	Entity* parent;
};
