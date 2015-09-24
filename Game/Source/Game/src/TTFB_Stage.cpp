#pragma once

#include <TTFB_Stage.h>
#include <MeshFactory.h>
#include <Box2DWorld.h>

TTFB_Stage::TTFB_Stage(float _width, Box2DWorld * _world, Shader* _shader) : 
	Entity(),
	width(_width)
{
	stageBase = new Box2DMeshEntity(_world, MeshFactory::getCubeMesh(_width * 0.5f), b2_staticBody, true, _shader);
	childTransform->addChild(stageBase);
	stageBase->setTranslationPhysical(0.f, -width * 0.5f, 0.f);
	stageBase->createFixture();
	_world->addToWorld(stageBase);
}

TTFB_Stage::~TTFB_Stage() {
}

void TTFB_Stage::setShader(Shader* _shader) {
	stageBase->setShader(_shader);
}