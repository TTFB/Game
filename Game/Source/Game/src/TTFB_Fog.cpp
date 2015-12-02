#pragma once

#include <TTFB_Fog.h>
#include <Sprite.h>
#include <TTFB_ResourceManager.h>

TTFB_Fog::TTFB_Fog(Shader* _shader) :
	Entity(), 
	flipDir(true)
{
	fog1 = new Sprite(_shader);
	fog1->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("fog1")->textureSampler);
	childTransform->addChild(fog1);

	fog2 = new Sprite(_shader);
	fog2->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("fog2")->textureSampler);
	childTransform->addChild(fog2);

	fog3 = new Sprite(_shader);
	fog3->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("fog3")->textureSampler);
	childTransform->addChild(fog3);

	fog4 = new Sprite(_shader);
	fog4->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("fog4")->textureSampler);
	childTransform->addChild(fog4);
}

void TTFB_Fog::update(Step* _step) {
	
	if(fog1->firstParent()->getTranslationVector().x >= 0.1f) {
		flipDir = true;
	}else if(fog1->firstParent()->getTranslationVector().x <= -0.1f) {
		flipDir = false;
	}

	int s = flipDir ? -1 : 1;

	fog1->firstParent()->translate(s * 0.0001f, 0.f ,0.f);
	fog2->firstParent()->translate(s * -0.0001f, 0.f ,0.f);
	fog3->firstParent()->translate(s * 0.0001f, 0.f ,0.f);
	fog4->firstParent()->translate(s * -0.0001f, 0.f ,0.f);

	Entity::update(_step);
}