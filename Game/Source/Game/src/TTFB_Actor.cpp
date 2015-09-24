#pragma once

#include <TTFB_Actor.h>

TTFB_Actor::TTFB_Actor(Box2DWorld * _world, Shader * _shader) :
	Box2DSprite(_world),
	moveAnimations(&moveVal),
	moveVal(0.f)
{
	setShader(_shader);
	createFixture(b2Filter());
	moveAnimations.startValue = 0.0f;
	moveAnimations.loopType = Animation<float>::LoopType::kLOOP;
	moveAnimations.hasStart = true;
}

TTFB_Actor::~TTFB_Actor() {
}

void TTFB_Actor::move(float _moveBy) {
	moveAnimations.tweens.push_back(new Tween<float>(3.f, _moveBy, Easing::kEASE_IN_OUT_EXPO));
}

void TTFB_Actor::update(Step* _step) {
	moveAnimations.update(_step);
	if(firstParent() != nullptr) {
		//firstParent()->translate(moveVal, 0.f, 0.f, false);
	}
	Box2DSprite::update(_step);
}