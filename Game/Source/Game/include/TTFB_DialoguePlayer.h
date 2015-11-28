#pragma once

#include <String>

class OpenAL_Sound;

class TTFB_DialoguePlayer {
public:
	TTFB_DialoguePlayer(std::string src);
	void playNext();
	void mute();
	void unmute();
private:
	std::string src;
	int current;
	bool muted;
	OpenAL_Sound * currentSound;
};