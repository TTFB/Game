#pragma once

#include <TTFB_SpamalotStage.h>
#include <MeshFactory.h>
#include <Box2DWorld.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>
#include <Sprite.h>

TTFB_SpamalotStage::TTFB_SpamalotStage(Box2DWorld * _world, Shader * _shader) :
	TTFB_Stage()
{
	stageBase = new Box2DMeshEntity(_world, MeshFactory::getCubeMesh(), b2_staticBody, _shader);
	stageBase->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("L1_Floor")->texture);
	childTransform->addChild(stageBase);
	stageBase->firstParent()->scale(100, 10.0f, 5.f);
	stageBase->createFixture();

	for(Vertex vert : stageBase->mesh->vertices) {
		vert.u *= 4;
		vert.v *= 4; 
	}

	stageBack = new Sprite(_shader);
	stageBack->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Background")->textureSampler);
	childTransform->addChild(stageBack);
	stageBack->firstParent()->scale(70, 70, 1.f);
	stageBack->firstParent()->translate(0.f, 19.f, -2.5f);

	stageFrontLeft = new Sprite(_shader);
	stageFrontLeft->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Side")->textureSampler);
	childTransform->addChild(stageFrontLeft);
	stageFrontLeft->firstParent()->scale(-50.0f, 70.0f, 1.f);
	stageFrontLeft->firstParent()->translate(-100 * 0.5f + 20.0f, 15.f, 3.5f);

	stageFrontRight = new Sprite(_shader);
	stageFrontRight->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Side")->textureSampler);
	childTransform->addChild(stageFrontRight);
	stageFrontRight->firstParent()->scale(50.0f, 70.0f, 1.f);
	stageFrontRight->firstParent()->translate(100 * 0.5f - 20.0f, 15.f, 3.5f);
	{
		stageTop = new Sprite(_shader);
		TextureSampler * top = TTFB_ResourceManager::scenario->getTextureSampler("L1_Top")->textureSampler;
		stageTop->setPrimaryTexture(top);
		childTransform->addChild(stageTop);
		stageTop->firstParent()->scale(100, 100, 1.f);
		stageTop->firstParent()->translate(0.f, 25.f, 3.0f);
	}
	{
		stageBottom = new Sprite(_shader);
		TextureSampler * bottom = TTFB_ResourceManager::scenario->getTextureSampler("L1_Bottom")->textureSampler;
		stageBottom->setPrimaryTexture(bottom);
		childTransform->addChild(stageBottom);
		stageBottom->firstParent()->scale(55, 55, 1.f);
		stageBottom->firstParent()->translate(0.f, 0.f, 2.5f);
	}

	curtainLeft = new Sprite(_shader);
	curtainLeft->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Curtain")->textureSampler);
	childTransform->addChild(curtainLeft);
	curtainLeft->firstParent()->scale(30 , 30, 30);
	curtainLeft->firstParent()->translate(-100 * 0.5f, 15.f, 2.5);

	curtainRight = new Sprite(_shader);
	curtainRight->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Curtain")->textureSampler);
	childTransform->addChild(curtainRight);
	curtainRight->firstParent()->scale(-30 , 30, 30);
	curtainRight->firstParent()->translate(100 * 0.5f, 15.f, 2.5f);
}
