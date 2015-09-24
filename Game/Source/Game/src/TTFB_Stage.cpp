#pragma once

#include <TTFB_Stage.h>
#include <MeshFactory.h>
#include <Box2DWorld.h>

TTFB_Stage::TTFB_Stage(float _width, Box2DWorld * _world, Shader* _shader) : 
	Entity(),
	width(_width)
{
	stageBase = new Box2DMeshEntity(_world, MeshFactory::getCubeMesh(), b2_staticBody, true, _shader);
	childTransform->addChild(stageBase);
	stageBase->firstParent()->scale(_width, 10.0f, 5.f);
	stageBase->createFixture();

	stageBack = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	childTransform->addChild(stageBack);
	stageBack->firstParent()->scale(_width * 1.5f, 50.0f, 1.f);
	stageBack->firstParent()->translate(0.f, 25.f, -2.5f);

	stageFrontLeft = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	childTransform->addChild(stageFrontLeft);
	stageFrontLeft->firstParent()->scale(-_width * 0.5f, 50.0f, 1.f);
	stageFrontLeft->firstParent()->translate(-_width * 0.5f, 25.f, 2.5f);

	stageFrontRight = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	childTransform->addChild(stageFrontRight);
	stageFrontRight->firstParent()->scale(_width * 0.5f, 50.0f, 1.f);
	stageFrontRight->firstParent()->translate(_width * 0.5f, 25.f, 2.5f);
}

TTFB_Stage::~TTFB_Stage() {
}

void TTFB_Stage::setShader(Shader* _shader) {
	stageBase->setShader(_shader);
}