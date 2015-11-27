#pragma once

#include <TTFB_DialoguePlayer.h>
#include <TTFB_ResourceManager.h>

TTFB_DialoguePlayer::TTFB_DialoguePlayer(std::string _source) :
	src(_source),
	current(1)
{
}

void TTFB_DialoguePlayer::playNext() {
	OpenAL_Sound * sound = TTFB_ResourceManager::scenario->getAudio(src + std::to_string(current))->sound;
	sound->play();
	current++;
}