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
#include <RenderOptions.h>
#include <TTFB_Prop.h>
#include <TTFB_Constants.h>

TTFB_Actor::TTFB_Actor(std::string _name, Box2DWorld * _world, BulletWorld * _bulletWorld, Font * _font, Shader * _textShader, Shader * _shader) :
	Box2DSuperSprite(_world, 0),
	speechArea(new TextArea(_bulletWorld, _font, _textShader, 1000.0f)),
	moveDirection(0),
	saySubscription(new TTFB_Subscription()),
	moveSubscription(new TTFB_Subscription()),
	speechAreaScale(0.01f),
	speedMod(1.0f),
	leftArmBroken(false),
	rightArmBroken(false),
	leftLegBroken(false),
	rightLegBroken(false)
{
	setShader(_shader, true);

	b2Filter filt;
	filt.categoryBits = Category::ACTOR;
	filt.maskBits     = Category::BOUNDARY | 0x000000;

	torso    = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "Torso")->textureSampler, b2_kinematicBody);
	head     = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "Head")->textureSampler);
	leftArm  = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "LeftArm")->textureSampler);
	rightArm = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "RightArm")->textureSampler);
	leftLeg	 = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "LeftLeg")->textureSampler);
	rightLeg = new Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_name + "RightLeg")->textureSampler);

	torso->scale    = B2_SCALE;
	head->scale     = B2_SCALE;
	leftArm->scale  = B2_SCALE;
	rightArm->scale = B2_SCALE;
	leftLeg->scale  = B2_SCALE;
	rightLeg->scale = B2_SCALE;

	//head->body->SetGravityScale(-0.3f);
	//leftArm->body->SetGravityScale(0.3f);
	///rightArm->body->SetGravityScale(0.3f);
	//legs->body->SetGravityScale(0.3f);

	torso->createFixture(filt)->SetDensity(1.f);
	head->createFixture(filt)->SetDensity(1.f);
	leftArm->createFixture(filt)->SetDensity(1.f);
	rightArm->createFixture(filt)->SetDensity(1.f);
	leftLeg->createFixture(filt)->SetDensity(1.f);
	rightLeg->createFixture(filt)->SetDensity(1.f);

	torso->maxVelocity = b2Vec2(5.0f, NO_VELOCITY_LIMIT);

	head->setTranslationPhysical(0.0f, 10.0f, 0.0f, true);
	torso->setTranslationPhysical(0.0f, 5.0f, 0.0f, true);
	leftArm->setTranslationPhysical(-5.0f, 0.0f, 0.0f, true);
	rightArm->setTranslationPhysical(5.0f, 0.0f, 0.0f, true);

	childTransform->addChild(speechArea);
	speechArea->firstParent()->scale(speechAreaScale, speechAreaScale, speechAreaScale);
	speechArea->setTranslationPhysical(0.f, 2.f, 0.f);
	speechArea->setBackgroundColour(1.0f, 1.0f, 1.0f, 1.0f);
	speechArea->horizontalAlignment = kCENTER;
	speechArea->setVisible(false);
	speechArea->background->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("speechBubble")->texture);
	speechArea->setPadding(50, 50, 100, 50);
	speechArea->setWrapMode(kWORD);

	//SpriteSheetAnimation * shWalk = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	//shWalk->pushFramesInRange(0, 26, 128, 150);
	
	//SpriteSheetAnimation * shStand = new SpriteSheetAnimation(TTFB_ResourceManager::scenario->getTexture("SPRITESHEET")->texture, 0.1f);
	//shStand->pushFramesInRange(7, 7, 128, 150);
	
	//torso->addAnimation("walk", shWalk, false);
	//torso->addAnimation("stand", shStand, true);

	// make the root component the torso
	addComponent(&leftArm);
	addComponent(&rightArm);
	addComponent(&leftLeg);
	addComponent(&rightLeg);
	addComponent(&torso);
	addComponent(&head);
	rootComponent = torso;

	b2RevoluteJointDef jth;
	jth.bodyA = torso->body;
	jth.bodyB = head->body;
	jth.localAnchorA.Set(0, 0.4f * torso->getCorrectedHeight());
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
	jtar.localAnchorA.Set(0.3f * torso->getCorrectedWidth(), 0.5f * torso->getCorrectedHeight());
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
	jtal.localAnchorA.Set(-0.3f * torso->getCorrectedWidth(), 0.5f * torso->getCorrectedHeight());
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
	jl.bodyB = leftLeg->body;
	jl.localAnchorA.Set(-0.3f * torso->getCorrectedWidth(), -0.4f * torso->getCorrectedHeight());
	jl.localAnchorB.Set(0,  0.5f * leftLeg->getCorrectedHeight());
	jl.collideConnected = false;
	jl.enableLimit = true;
	jl.enableMotor = true;
	jl.maxMotorTorque = 0;
	jl.motorSpeed = 0;
	jl.referenceAngle = 0;
	jl.lowerAngle = glm::radians(-15.f);
	jl.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&jl);
	
	b2RevoluteJointDef jr;
	jr.bodyA = torso->body;
	jr.bodyB = rightLeg->body;
	jr.localAnchorA.Set(0.3f * torso->getCorrectedWidth(), -0.4f * torso->getCorrectedHeight());
	jr.localAnchorB.Set(0,  0.5f * rightLeg->getCorrectedHeight());
	jr.collideConnected = false;
	jr.enableLimit = true;
	jr.enableMotor = true;
	jr.maxMotorTorque = 0;
	jr.motorSpeed = 0;
	jr.referenceAngle = 0;
	jr.lowerAngle = glm::radians(-15.f);
	jr.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&jr);
	
	leftArmJointTransform = new Transform();
	torso->childTransform->addChild(leftArmJointTransform);
	leftArmJointTransform->firstParent()->translate(-0.4 * torso->getCorrectedWidth(), 0.4 * torso->getCorrectedHeight(), 0.0f);

	rightArmJointTransform = new Transform();
	torso->childTransform->addChild(rightArmJointTransform);
	rightArmJointTransform->firstParent()->translate(-0.4 * torso->getCorrectedWidth(), 0.4 * torso->getCorrectedHeight(), 0.0f);

	leftLegJointTransform = new Transform();
	torso->childTransform->addChild(leftLegJointTransform);
	leftLegJointTransform->firstParent()->translate(-0.3 * torso->getCorrectedWidth(), -0.4 * torso->getCorrectedHeight(), 0.0f);

	rightLegJointTransform = new Transform();
	torso->childTransform->addChild(rightLegJointTransform);
	rightLegJointTransform->firstParent()->translate(0.3 * torso->getCorrectedWidth(), -0.4 * torso->getCorrectedHeight(), 0.0f);
}

TTFB_Actor::~TTFB_Actor() {
}

TTFB_Subscription * TTFB_Actor::move(float _moveBy) {
	b2Vec2 pos = torso->body->GetPosition();
	if(_moveBy - pos.x > 0) {
		moveDirection = 1;
	}else if(_moveBy - pos.x  < 0) {
		moveDirection = -1;	
	}else {
		moveDirection = 0;
	}
	float target = _moveBy; 
	if(firstParent() != nullptr){
		when([target, this](){
			float curX = rootComponent->body->GetPosition().x;
			return moveDirection > 0 ? curX > target : curX < target;
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
		head->meshTransform->scale(-1 * firstParent()->getScaleVector().x, 1.f, 1.f);
		leftLeg->meshTransform->scale(-1 * firstParent()->getScaleVector().x, 1.f, 1.f);
		rightLeg->meshTransform->scale(-1 * firstParent()->getScaleVector().x, 1.f, 1.f);
	}
}

void TTFB_Actor::breakLeftArmJoint() {
	if(!leftArmBroken){
		breakJoint(leftArm);
		leftArmBroken = true;
	}
}

void TTFB_Actor::breakLeftLegJoint(){
	if(!leftLegBroken){
		breakJoint(leftLeg);
		leftLegBroken = true;
	}
}

void TTFB_Actor::breakRightLegJoint(){
	if(!rightLegBroken){
		breakJoint(rightLeg);
		rightLegBroken = true;
	}
}

void TTFB_Actor::breakRightArmJoint(){
	if(!rightArmBroken){
		breakJoint(rightArm);
		rightArmBroken = true;
	}
}

void TTFB_Actor::applyImpulseLeftArm(float _x, float _y) {
	b2Vec2 center = leftArm->body->GetWorldCenter();
	leftArm->applyLinearImpulse(_x ,_y, center.x, center.y);
}

void TTFB_Actor::applyImpulseRighttArm(float _x, float _y) {
	b2Vec2 center = rightArm->body->GetWorldCenter();
	rightArm->applyLinearImpulse(_x ,_y, center.x, center.y);
}

void TTFB_Actor::applyImpulseLegs(float _x, float _y) {
	{
		b2Vec2 center = leftLeg->body->GetWorldCenter();
		leftLeg->applyLinearImpulse(_x ,_y, center.x, center.y);
	}
	{
		b2Vec2 center = rightLeg->body->GetWorldCenter();
		rightLeg->applyLinearImpulse(_x ,_y, center.x, center.y);
	}
}

void TTFB_Actor::pickupPropLeft(TTFB_Prop * _prop) {
	b2RevoluteJointDef joint;
	joint.bodyA = leftArm->body;
	joint.bodyB = _prop->body;
	joint.localAnchorA.Set(-0.5f * leftArm->getCorrectedWidth(), 0);
	joint.localAnchorB.Set(0, -_prop->getCorrectedWidth() * 0.45f);
	joint.collideConnected = false;
	joint.enableLimit = true;
	joint.enableMotor = true;
	joint.maxMotorTorque = 0;
	joint.motorSpeed = 0;
	joint.referenceAngle = 0;
	joint.lowerAngle = glm::radians(-15.f);
	joint.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&joint);
}

void TTFB_Actor::swingRightArm() {
	b2Vec2 point = rightArm->body->GetWorldCenter();
	rightArm->applyLinearImpulse(0.0f, 200.0f, point.x, point.y);
}

void TTFB_Actor::swingLeftArm() {
	b2Vec2 point= leftArm->body->GetWorldCenter();
	leftArm->applyLinearImpulse(0.0f, 200.0f, point.x, point.y);
}

b2Vec2 TTFB_Actor::getBox2dPos() {
	return torso->body->GetPosition();
}

void TTFB_Actor::pickupPropRight(TTFB_Prop* _prop) {
	b2RevoluteJointDef joint;
	joint.bodyA = rightArm->body;
	joint.bodyB = _prop->body;
	joint.localAnchorA.Set(0.5f * rightArm->getCorrectedWidth(), 0);
	joint.localAnchorB.Set(0, -_prop->getCorrectedWidth() * 0.45f);
	joint.collideConnected = false;
	joint.enableLimit = true;
	joint.enableMotor = true;
	joint.maxMotorTorque = 0;
	joint.motorSpeed = 0;
	joint.referenceAngle = 0;
	joint.lowerAngle = glm::radians(-15.f);
	joint.upperAngle = glm::radians(15.f);
	world->b2world->CreateJoint(&joint);
}

void TTFB_Actor::applyImpulseHead(float _x, float _y) {
	b2Vec2 center = head->body->GetWorldCenter();
	head->applyLinearImpulse(_x ,_y, center.x, center.y);
}

void TTFB_Actor::breakHeadJoint() {
	breakJoint(head);
}

void TTFB_Actor::breakJoint(Box2DSprite* _sprite) {
	world->b2world->DestroyJoint(_sprite->body->GetJointList()->joint);
}

float TTFB_Actor::getLegsOffset() {
	return torso->getCorrectedHeight() * 0.5 + leftLeg->getCorrectedHeight();
}

void TTFB_Actor::update(Step* _step) {
	TTFB_Whenable::update(_step);
	float curX = rootComponent->body->GetPosition().x;
	float curY = rootComponent->body->GetPosition().y;
	float targX = curX + (1.0f * moveDirection *speedMod * 0.05 * _step->deltaTimeCorrection);
	rootComponent->setTranslationPhysical(targX, curY, 0.f);
	speechArea->firstParent()->translate(head->body->GetWorldCenter().x - speechArea->getWidth() * 0.5f * speechAreaScale,
		head->body->GetWorldCenter().y + speechArea->getHeight() * 0.5f * speechAreaScale + 1.0f,
		speechArea->firstParent()->getTranslationVector().z, false);
	Box2DSuperSprite::update(_step);
}

void TTFB_Actor::render(sweet::MatrixStack* _matrixStack, RenderOptions* _renderOptions) {\
	Entity::render(_matrixStack, _renderOptions);
}