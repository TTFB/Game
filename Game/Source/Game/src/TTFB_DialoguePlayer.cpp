#pragma once

#include <TTFB_DialoguePlayer.h>
#include <TTFB_ResourceManager.h>
#include <OpenALSound.h>

TTFB_DialoguePlayer::TTFB_DialoguePlayer(std::string _source) :
	src(_source),
	current(1),
	muted(false),
	currentSound(nullptr),
	playing(true)
{
}

TTFB_DialoguePlayer::~TTFB_DialoguePlayer() {
	if(currentSound != nullptr){
		currentSound->stop();
	}
}

void TTFB_DialoguePlayer::mute() {
	muted = true; 
	if(currentSound != nullptr){
		currentSound->setGain(0);
	}
}

void TTFB_DialoguePlayer::unmute() {
	muted = false; 
	if(currentSound != nullptr){
		currentSound->setGain(1);
	}
}

void TTFB_DialoguePlayer::playNext() {
	if(playing){
		OpenAL_Sound * sound = TTFB_ResourceManager::scenario->getAudio(src + std::to_string(current))->sound;
		sound->play();
		currentSound = sound;
		sound->setGain((float)((int) !muted));
		current++;
	}
}