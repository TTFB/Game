#pragma once

#include <TTFB_Stage.h>
#include <Sprite.h>

TTFB_Stage::TTFB_Stage() : 
	Entity(),
	stageBase(nullptr),
	stageBack(nullptr),
	stageFrontLeft(nullptr),
	stageFrontRight(nullptr),
	stageBottom(nullptr),
	stageTop(nullptr),
	curtainLeft(nullptr),
	curtainRight(nullptr)
{
}

TTFB_Stage::~TTFB_Stage() {
}

sweet::Rectangle TTFB_Stage::getVisibleBounds() const {
	float left;
	float right;
	float top;
	float bottom;

	left = stageFrontLeft->firstParent()->getTranslationVector().x + stageFrontLeft->firstParent()->getScaleVector().x * 0.5f;
	right = stageFrontRight->firstParent()->getTranslationVector().x - stageFrontRight->firstParent()->getScaleVector().x * 0.5f;
	top = stageTop->firstParent()->getTranslationVector().y + 5.f;// + stageTop->firstParent()->getScaleVector().y * 0.5f;
	bottom = stageBase->firstParent()->getTranslationVector().y + stageBase->firstParent()->getScaleVector().y * 0.5f;

	return sweet::Rectangle(left, bottom, right - left, top - bottom);
}
