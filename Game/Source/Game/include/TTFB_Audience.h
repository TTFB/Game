#pragma once

#include <Sprite.h>
#include <OpenALSound.h>

class TTFB_Audience : public Sprite {
public:

	TTFB_Audience(std::string _prefix, Shader * _shader);
	~TTFB_Audience();

	void update(Step * _step) override;

	void setNeutral();
	void setHappy(int _level);
	void setBored(int _level);
	void stopAudio();

private:
	int currentState;
	double lastSoundPlayed;
	std::string prefix;
	bool playAudio;

	OpenAL_Sound * clapping;
	OpenAL_Sound * snoring;
};