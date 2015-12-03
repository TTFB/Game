#pragma once

#include <TTFB_Stage.h>
#include <MeshFactory.h>
#include <Box2DWorld.h>
#include <MeshInterface.h>
#include <TTFB_ResourceManager.h>

TTFB_Stage::TTFB_Stage(float _width, Box2DWorld * _world, std::string _floorTex, std::string _sideTex, std::string _backTex, std::string _topTex, std::string _bottomTex, Shader * _shader) : 
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
	stageFrontLeft->firstParent()->translate(-_width * 0.5f + 1.0f, 15.f, 3.5f);

	stageFrontRight = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
	stageFrontRight->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture(_sideTex)->texture);
	childTransform->addChild(stageFrontRight);
	stageFrontRight->firstParent()->scale(_width * 0.5f, 50.0f, 1.f);
	stageFrontRight->firstParent()->translate(_width * 0.5f - 1.0f, 15.f, 3.5f);

	{
		stageTop = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
		Texture * top = TTFB_ResourceManager::scenario->getTexture(_topTex)->texture;
		stageTop->mesh->pushTexture2D(top);
		float ratio = (float)top->height/(float)top->width;
		childTransform->addChild(stageTop);
		stageTop->firstParent()->scale(_width * 0.5f,  ratio * _width * 0.5f, 1.f);
		stageTop->firstParent()->translate(0.f, 25.f, 3.0f);
	}

	{
		stageBottom = new MeshEntity(MeshFactory::getPlaneMesh(), _shader);
		Texture * bottom = TTFB_ResourceManager::scenario->getTexture(_bottomTex)->texture;
		stageBottom->mesh->pushTexture2D(bottom);
		float ratio = (float)bottom->height/(float)bottom->width;
		childTransform->addChild(stageBottom);
		stageBottom->firstParent()->scale(_width * 0.65f,  ratio * _width * 0.65f, 1.f);
		stageBottom->firstParent()->translate(0.f, -0.5f, 3.0f);
	}

	curtainLeft = new Sprite(_shader);
	curtainLeft->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Curtain")->textureSampler);
	childTransform->addChild(curtainLeft);
	curtainLeft->firstParent()->scale(35 , 30, 30);
	curtainLeft->firstParent()->translate(-_width * 0.5f, 15.f, 1.5);

	curtainRight = new Sprite(_shader);
	curtainRight->setPrimaryTexture(TTFB_ResourceManager::scenario->getTextureSampler("L1_Curtain")->textureSampler);
	childTransform->addChild(curtainRight);
	curtainRight->firstParent()->scale(-35 , 30, 30);
	curtainRight->firstParent()->translate(_width * 0.5f, 15.f, 1.5f);
}

TTFB_Stage::~TTFB_Stage() {
}

void TTFB_Stage::setShader(Shader* _shader) {
	stageBase->setShader(_shader);
}

sweet::Rectangle TTFB_Stage::getVisibleBounds() {
	float left = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	float bottom = 0.0f;

	left = stageFrontLeft->firstParent()->getTranslationVector().x + stageFrontLeft->firstParent()->getScaleVector().x * 0.5f;
	right = stageFrontRight->firstParent()->getTranslationVector().x - stageFrontRight->firstParent()->getScaleVector().x * 0.5f;
	top = stageTop->firstParent()->getTranslationVector().y - stageTop->firstParent()->getScaleVector().y * 0.5f;
	bottom = stageBase->firstParent()->getTranslationVector().y + stageBase->firstParent()->getScaleVector().y * 0.5f;

	return sweet::Rectangle(left, bottom, right - left, top - bottom);
}