#pragma once

class Animation {
public:
	Animation(float duration, float startOffset = 0);
	void play(float deltaTime);

private:
	float duration;
	float startOffset;
};