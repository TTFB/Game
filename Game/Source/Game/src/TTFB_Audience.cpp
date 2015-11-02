#pragma once

#include <TTFB_Audience.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>


TTFB_Audience::TTFB_Audience(Shader * _shader) :
	Sprite(_shader)
{
	mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("audience")->texture);
}

TTFB_Audience::~TTFB_Audience() {
}

void TTFB_Audience::update(Step* _step) {
	Sprite::update(_step);
}