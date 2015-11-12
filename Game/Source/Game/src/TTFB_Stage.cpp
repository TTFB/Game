#pragma once

#include <TTFB_Stage.h>
#include <MeshFactory.h>
#include <Box2DWorld.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>

TTFB_Stage::TTFB_Stage(float _width, Box2DWorld * _world, std::string _floorTex, std::string _sideTex, std::string _backTex, Shader * _shader) : 
	Entity(),
	width(_width)
{

	stageBase = new Box2DMeshEntity(_world, MeshFactory::getCubeMesh(), b2_staticBody, true, _shader);
	stageBase->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture(_floorTex)->texture);
	childTransform->addChild(stageBase);
	stageBase->firstParent()->scale(_width, 10.0f, 5.f);
	stageBase->createFixture();

	for(Vertex vert : stageBase->mesh->vertices) {
		vert.u *= 4;
		vert.v *= 4; 
	}

	stageBack = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	stageBack->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture(_backTex)->texture);
	childTransform->addChild(stageBack);
	stageBack->firstParent()->scale(_width * 1.5f, 50.0f, 1.f);
	stageBack->firstParent()->translate(0.f, 30.f, -2.5f);

	stageFrontLeft = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	stageFrontLeft->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture(_sideTex)->texture);
	childTransform->addChild(stageFrontLeft);
	stageFrontLeft->firstParent()->scale(-_width * 0.5f, 50.0f, 1.f);
	stageFrontLeft->firstParent()->translate(-_width * 0.5f, 15.f, 3.f);

	stageFrontRight = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	stageFrontRight->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture(_sideTex)->texture);
	childTransform->addChild(stageFrontRight);
	stageFrontRight->firstParent()->scale(_width * 0.5f, 50.0f, 1.f);
	stageFrontRight->firstParent()->translate(_width * 0.5f, 15.f, 3.f);
}

TTFB_Stage::~TTFB_Stage() {
}

void TTFB_Stage::setShader(Shader* _shader) {
	stageBase->setShader(_shader);
}