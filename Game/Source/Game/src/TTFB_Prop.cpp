#pragma once

#include <TTFB_Prop.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>

TTFB_Prop::TTFB_Prop(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader) :
	Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_samplerResourceId)->textureSampler)
{
	b2Filter filt;
	filt.categoryBits = Category::PROP;
	filt.maskBits     = 0x000000;

	setShader(_shader);
	scale = 0.01f;
	createFixture(filt);
}