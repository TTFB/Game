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
#include <Box2DSprite.h>

TTFB_Actor::TTFB_Actor(Box2DWorld * _world, BulletWorld * _bulletWorld, Scene * _scene, Font * _font, Shader * _textShader, Shader * _shader) :
	Box2DSuperSprite(_world, 0),
	speechArea(new TextArea(_bulletWorld, _scene, _font, _textShader, 200.0f)),
	moveDirection(0),
	saySubscription(new TTFB_Subscription()),
	moveSubscription(new TTFB_Subscription())
{
	setShader(_shader, true);

	b2Filter filt;
	filt.categoryBits = Category::ACTOR;
	filt.maskBits     = Category::BOUNDARY | 0x000000;

	torso    = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler("kingArthurTorso")->textureSampler, b2_kinematicBody);
	head     = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler("kingArthurHead")->textureSampler);
	leftArm  = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler("kingArthurLeftArm")->textureSampler);
	rightArm = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler("kingArthurRightArm")->textureSampler);
	legs	 = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler("kingArthurLegs")->textureSampler);

	torso->scale    = 0.01f;
	head->scale     = 0.01f;
	leftArm->scale  = 0.01f;
	rightArm->scale = 0.01f;
	legs->scale     = 0.01f;

	head->body->SetGravityScale(-0.3f);
	leftArm->body->SetGravityScale(0.3f);
	rightArm->body->SetGravityScale(0.3f);
	legs->body->SetGravityScale(0.3f);

	torso->createFixture(filt)->SetDensity(0.f);
	head->createFixture(filt)->SetDensity(0.f);
	leftArm->createFixture(filt)->SetDensity(0.f);
	rightArm->createFixture(filt)->SetDensity(0.f);
	legs->createFixture(filt)->SetDensity(100000.0f);

	torso->maxVelocity = b2Vec2(5.0f, NO_VELOCITY_LIMIT);

	head->setTranslationPhysical(0.0f, 10.0f, 0.0f, true);
	torso->setTranslationPhysical(0.0f, 5.0f, 0.0f, true);
	leftArm->setTranslationPhysical(-5.0f, 0.0f, 0.0f, true);
	rightArm->setTranslationPhysical(5.0f, 0.0f, 0.0f, true);

	head->childTransform->addChild(speechArea);
	speechArea->firstParent()->scale(0.05f, 0.05f, 0.05f);
	speechArea->setTranslationPhysical(0.f, 2.f, 0.f);
	speechArea->setBackgroundColour(1.0f, 1.0f, 1.0f, 1.0f);
	speechArea->horizontalAlignment = kCENTER;
	speechArea->setVisible(false);

	//SpriteSheetAnimation * shWalk = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	//shWalk->pushFramesInRange(0, 26, 128, 150);
	
	//SpriteSheetAnimation * shStand = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	//shStand->pushFramesInRange(7, 7, 128, 150);
	
	//torso->addAnimation("walk", shWalk, false);
	//torso->addAnimation("stand", shStand, true);

	// make the root component the torso
	addComponent(&torso);
	addComponent(&head);
	addComponent(&leftArm);
	addComponent(&rightArm);
	addComponent(&legs);
	rootComponent = torso;

	b2RevoluteJointDef jth;
	jth.bodyA = torso->body;
	jth.bodyB = head->body;
	jth.localAnchorA.Set(0, 0.5f * torso->getCorrectedHeight());
	jth.localAnchorB.Set(0, -0.5f * head->getCorrectedHeight());
	jth.collideConnected = false;
	jth.enableLimit = true;
	jth.enableMotor = true;
	jth.maxMotorTorque = 0;
	jth.motorSpeed = 0;
	jth.referenceAngle = 0;
	jth.lowerAngle = glm::radians(-15.f);
	jth.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&jth);

	b2RevoluteJointDef jtar;
	jtar.bodyA = torso->body;
	jtar.bodyB = rightArm->body;
	jtar.localAnchorA.Set(0.5f * torso->getCorrectedWidth(), 0.5f * torso->getCorrectedHeight());
	jtar.localAnchorB.Set(-0.5f * rightArm->getCorrectedWidth(), 0.5f * rightArm->getCorrectedHeight());
	jtar.collideConnected = false;
	jtar.enableLimit = true;
	jtar.enableMotor = true;
	jtar.maxMotorTorque = 0;
	jtar.motorSpeed = 0;
	jtar.referenceAngle = glm::radians(0.f);
	jtar.lowerAngle = glm::radians(-10.f);
	jtar.upperAngle = glm::radians(10.f);
	world->b2world->CreateJoint(&jtar);

	b2RevoluteJointDef jtal;
	jtal.bodyA = torso->body;
	jtal.bodyB = leftArm->body;
	jtal.localAnchorA.Set(-0.5f * torso->getCorrectedWidth(), 0.5f * torso->getCorrectedHeight());
	jtal.localAnchorB.Set(0.5f * leftArm->getCorrectedWidth(), 0.5f * leftArm->getCorrectedHeight());
	jtal.collideConnected = false;
	jtal.enableLimit = true;
	jtal.enableMotor = true;
	jtal.maxMotorTorque = 0;
	jtal.motorSpeed = 0;
	jtal.referenceAngle = glm::radians(0.f);
	jtal.lowerAngle = glm::radians(-10.f);
	jtal.upperAngle = glm::radians(10.f);
	world->b2world->CreateJoint(&jtal);

	b2RevoluteJointDef jl;
	jl.bodyA = torso->body;
	jl.bodyB = legs->body;
	jl.localAnchorA.Set(0, -0.5f * torso->getCorrectedHeight());
	jl.localAnchorB.Set(0,  0.5f * legs->getCorrectedHeight());
	jl.collideConnected = false;
	jl.enableLimit = true;
	jl.enableMotor = true;
	jl.maxMotorTorque = 0;
	jl.motorSpeed = 0;
	jl.referenceAngle = 0;
	jl.lowerAngle = glm::radians(-15.f);
	jl.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&jl);
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
			float curX = rootComponent->body->GetPosition().x;
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
		rootComponent->meshTransform->scale(-1 * firstParent()->getScaleVector().x, 1.f, 1.f);
	}
}

void TTFB_Actor::update(Step* _step) {
	TTFB_Whenable::update(_step);
	rootComponent->setTranslationPhysical(1.0f * moveDirection * 0.05f, 0.f, 0.f, true);
	Box2DSuperSprite::update(_step);
}