#pragma once

#include <TTFB_Audience.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>
#include <NumberUtils.h>


TTFB_Audience::TTFB_Audience(std::string _prefix, Shader * _shader) :
	Sprite(_shader),
	currentState(0),
	lastSoundPlayed(0.0),
	prefix(_prefix),
	playAudio(true),
	clapping(nullptr),
	snoring(nullptr)
{
	setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdNeutral")->textureSampler);

	clapping =  TTFB_ResourceManager::scenario->getAudio("clapping1")->sound;
	clapping->setGain(0.3f);

	snoring =  TTFB_ResourceManager::scenario->getAudio("snore4")->sound;
	snoring->setGain(0.3f);
}

TTFB_Audience::~TTFB_Audience() {
}

void TTFB_Audience::setNeutral() {
	if(currentState != 0){
		setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdNeutral")->textureSampler);
		currentState = 0;
	}
}

void TTFB_Audience::setHappy(int _level) {
	if(currentState != _level){
		if(_level < 3){
			setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdHappy" + std::to_string(_level))->textureSampler);
		}else {
			setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdHappy3")->textureSampler);
		}
		currentState = _level;
	}
}

void TTFB_Audience::setBored(int _level) {
	if(currentState != -_level){
		if(_level < 4){
			setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdBored" + std::to_string(_level))->textureSampler);
		}else {
			setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler(prefix + "_CrowdBored4")->textureSampler);
		}
		currentState = -_level;
	}
}

void TTFB_Audience::stopAudio() {
	clapping->stop();
	snoring->stop();
	playAudio = false;
}

void TTFB_Audience::update(Step* _step) {
	if(playAudio){
		if(lastSoundPlayed > 8.0){
			if(currentState > 0) {
				int i = sweet::NumberUtils::randomInt(0, 600 - currentState);
				if(i < 30) {
					clapping->play();
					lastSoundPlayed = 0;
				}
			}else if(currentState < 0) {
				int i = sweet::NumberUtils::randomInt(0, 600 + currentState);
				if(i < 30) {
					snoring->play();
					lastSoundPlayed = 0;
				}
			}
		}
		lastSoundPlayed += _step->deltaTime;
	}
	Sprite::update(_step);
}
