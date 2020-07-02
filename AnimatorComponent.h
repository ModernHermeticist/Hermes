#pragma once

class Entity;

class AnimatorComponent
{
public:
	AnimatorComponent(int _animationStart, int _animationEnd, int _currentFrame, float _animationScale, bool _forwardAndReverse);
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

	bool getPlayAnimation();
	void setPlayAnimation(bool _playAnimation);

	std::chrono::steady_clock::time_point getTime();
	void setTime(std::chrono::steady_clock::time_point _time);

private:
	int animationStart;
	int animationEnd;
	float animationScale;
	bool animationForward;

	bool playAnimation = true;

	int currentFrame;

	bool forwardAndReverse;

	Entity* parent;
	std::chrono::high_resolution_clock Clock;

	std::chrono::steady_clock::time_point time;
};
