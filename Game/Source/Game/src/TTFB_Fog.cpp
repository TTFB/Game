#pragma once

#include <TTFB_Fog.h>
#include <Sprite.h>
#include <TTFB_ResourceManager.h>

TTFB_Fog::TTFB_Fog(Shader* _shader) :
	Entity()
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
	Entity::update(_step);
}