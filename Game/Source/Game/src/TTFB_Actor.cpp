#pragma once

#include <TTFB_Actor.h>
#include <TextArea.h>
#include <Box2DWorld.h>
#include <BulletWorld.h>
#include <Scene.h>
#include <Font.h>
#include <Sweet.h>
#include <TTFB_ResourceManager.h>
#include <SpriteSheetAnimation.h>
#include <TTFB_Subscription.h>

TTFB_Actor::TTFB_Actor(Box2DWorld * _world, BulletWorld * _bulletWorld, Scene * _scene, Font * _font, Shader * _textShader, Shader * _shader) :
	Box2DSprite(_world),
	speechArea(new TextArea(_bulletWorld, _scene, _font, _textShader, 200.0f)),
	moveDirection(0),
	saySubscription(new TTFB_Subscription()),
	moveSubscription(new TTFB_Subscription())
{
	setShader(_shader);
	createFixture();
	maxVelocity = b2Vec2(5.0f, NO_VELOCITY_LIMIT);

	childTransform->addChild(speechArea);
	speechArea->firstParent()->scale(0.05f, 0.05f, 0.05f);
	speechArea->setTranslationPhysical(0.f, 2.f, 0.f);
	speechArea->setBackgroundColour(1.0f, 1.0f, 1.0f, 1.0f);
	speechArea->setVisible(false);

	SpriteSheetAnimation * shWalk = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	shWalk->pushFramesInRange(0, 26, 128, 150);
	
	SpriteSheetAnimation * shStand = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	shStand->pushFramesInRange(7, 7, 128, 150);
	
	addAnimation("walk", shWalk, false);
	addAnimation("stand", shStand, true);
}

TTFB_Actor::~TTFB_Actor() {
}

TTFB_Subscription * TTFB_Actor::move(float _moveBy) {
	if(_moveBy > 0) {
		moveDirection = 1;
	}else if(_moveBy < 0) {
		moveDirection = -1;	
	}else {
		moveDirection = 0;
	}
	float target = firstParent()->getTranslationVector().x + _moveBy; 
	if(firstParent() != nullptr){
		when([target, this](){
			float curX = body->GetPosition().x;
			return abs(curX) >= abs(target);
		},
		[this](){
			moveDirection = 0;
			moveSubscription->publish();
		});
	}
	return moveSubscription;
}

TTFB_Subscription * TTFB_Actor::say(float _durationSeconds, std::wstring _say, bool _hideOnComplete) {
	long targetTime = sweet::step.time + _durationSeconds;
	speechArea->setVisible(true);
	speechArea->setText(_say);
	when([targetTime, this](){
		return targetTime < sweet::step.time;
	},
	[this, _hideOnComplete](){
		speechArea->setVisible(!_hideOnComplete);
		saySubscription->publish();
	});
	return saySubscription;
}

void TTFB_Actor::flip() {
	if(firstParent() != nullptr) {
		meshTransform->scale(-1 * firstParent()->getScaleVector().x, 1.f, 1.f);
	}
}

void TTFB_Actor::update(Step* _step) {
	TTFB_Whenable::update(_step);
	applyForce(moveDirection * 5.0f, 0.f, body->GetWorldCenter().x, body->GetWorldCenter().y);
	Box2DSprite::update(_step);
}