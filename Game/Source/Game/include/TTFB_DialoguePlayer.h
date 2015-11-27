#pragma once

#include <String>

class TTFB_DialoguePlayer {
public:
	TTFB_DialoguePlayer(std::string src);
	void playNext();

private:
	std::string src;
	int current;
};