#pragma once

#include <Sprite.h>

class TTFB_Audience : public Sprite {
public:

	TTFB_Audience(Shader * _shader);
	~TTFB_Audience();

	void update(Step * _step) override;

	void setNeutral();

	void setHappy(int _level);

	void setBored(int _level);

private:
	int currentState;
	double lastSoundPlayed;
};