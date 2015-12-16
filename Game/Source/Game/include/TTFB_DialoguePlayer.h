#pragma once

#include <String>

class OpenAL_Sound;

class TTFB_DialoguePlayer {
public:

	bool playing;

	TTFB_DialoguePlayer(std::string src);
	~TTFB_DialoguePlayer();

	void playNext();
	void mute();
	void unmute();
	bool muted;
private:
	std::string src;
	int current;
	OpenAL_Sound * currentSound;
};