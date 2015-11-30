#pragma once

#include <String>

class OpenAL_Sound;

class TTFB_DialoguePlayer {
public:
	TTFB_DialoguePlayer(std::string src);
	void playNext();
	void mute();
	void unmute();
	bool muted;
private:
	std::string src;
	int current;
	OpenAL_Sound * currentSound;
};