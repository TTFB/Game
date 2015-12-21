#pragma once

#include <TTFB_Prop.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Constants.h>

TTFB_Prop::TTFB_Prop(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader, float _scaleMult) :
	Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_samplerResourceId)->textureSampler)
{
	b2Filter filt;
	filt.categoryBits = Category::PROP;
	filt.maskBits     = 0x000000;
	setShader(_shader);

	scale = B2_SCALE * _scaleMult;
	createFixture(filt);
}