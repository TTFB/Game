#pragma once

#include <TTFB_Audience.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>
#include <NumberUtils.h>


TTFB_Audience::TTFB_Audience(Shader * _shader) :
	Sprite(_shader),
	currentState(0),
	lastSoundPlayed(0.0)
{
	mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdNeutral")->texture);
}

TTFB_Audience::~TTFB_Audience() {
}

void TTFB_Audience::setNeutral() {
	if(currentState != 0){
		mesh->popTexture2D();
		mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdNeutral")->texture);
		currentState = 0;
	}
}

void TTFB_Audience::setHappy(int _level) {
	if(currentState != _level){
		mesh->popTexture2D();
		if(_level < 3){
			mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdHappy" + std::to_string(_level))->texture);
		}else {
			mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdHappy3")->texture);
		}
		currentState = _level;
	}
}

void TTFB_Audience::setBored(int _level) {
	if(currentState != -_level){
		mesh->popTexture2D();
		if(_level < 4){
			mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdBored" + std::to_string(_level))->texture);
		}else {
			mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_CrowdBored4")->texture);
		}
		currentState = -_level;
	}
}

void TTFB_Audience::update(Step* _step) {

	if(lastSoundPlayed > 8.0){
		if(currentState > 0) {
			int i = sweet::NumberUtils::randomInt(0, 600 - currentState);
			if(i < 30) {
				OpenAL_Sound * sound =  TTFB_ResourceManager::scenario->getAudio("clapping1")->sound;
				sound->setGain(0.3f);
				sound->play();
				lastSoundPlayed = 0;
			}
		
		}else if(currentState < 0) {
			int i = sweet::NumberUtils::randomInt(0, 600 + currentState);
			if(i < 30) {
				OpenAL_Sound * sound =  TTFB_ResourceManager::scenario->getAudio("snore4")->sound;
				sound->setGain(0.3f);
				sound->play();
				lastSoundPlayed = 0;
			}
		}
	}

	lastSoundPlayed += _step->deltaTime;

	Sprite::update(_step);
}