#pragma once

#include <TTFB_Audience.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>


TTFB_Audience::TTFB_Audience(Shader * _shader) :
	Sprite(_shader),
	currentState(0)
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
	Sprite::update(_step);
}