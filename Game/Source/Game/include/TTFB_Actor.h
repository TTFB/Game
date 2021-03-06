#pragma once

#include <Box2DSuperSprite.h>
#include <TTFB_Whenable.h>

#include <string>

class TTFB_Prop;
class TextArea;
class BulletWorld;
class Scene;
class Font;
class TTFB_Subscription;

enum Category {
	BOUNDARY =          0x0001,
    ACTOR	 =          0x0002,
	PROP     =			0x0004,
	SET_PIECE =			0x0008
    //ENEMY_SHIP =        0x0004,
    //FRIENDLY_AIRCRAFT = 0x0008,
    //ENEMY_AIRCRAFT =    0x0010,
};

class TTFB_Actor : public Box2DSuperSprite, public TTFB_Whenable{
public:

	float speedMod;

	Box2DSprite * torso;
	Box2DSprite * head;
	Box2DSprite * leftArm;
	Box2DSprite * rightArm;
	Box2DSprite* rightLeg;
	Box2DSprite* leftLeg;

	Transform * leftArmJointTransform;
	Transform * rightArmJointTransform;
	Transform * leftLegJointTransform;
	Transform * rightLegJointTransform;

	TTFB_Actor(std::string _name, Box2DWorld * _world, BulletWorld * _bulletWorld, Font * _font, Shader * _textShader, Shader * _shader = nullptr);
	~TTFB_Actor();

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual TTFB_Subscription * move(float _moveBy);
	TTFB_Subscription* moveY(float _moveBy);
	virtual TTFB_Subscription * say(float _durationSeconds, std::wstring _say, bool _hideOnComplete);
	virtual void flip();
	virtual float getLegsOffset();

	void breakLeftArmJoint();
	void breakRightArmJoint();
	void breakLeftLegJoint();
	void breakRightLegJoint();
	void breakHeadJoint();

	void applyImpulseLeftArm(float _x, float _y);
	void applyImpulseRighttArm(float _x, float _y);
	void applyImpulseLegs(float _x, float _y);
	void applyImpulseHead(float _x, float _y);

	void pickupPropLeft(TTFB_Prop * _prop);
	void pickupPropRight(TTFB_Prop * _prop);

	void swingRightArm();
	void swingLeftArm();

	b2Vec2 getBox2dPos();

	bool leftArmBroken;
	bool rightArmBroken;
	bool leftLegBroken;
	bool rightLegBroken;

private:
	TextArea * speechArea; 
	TTFB_Subscription * moveSubscription;
	TTFB_Subscription * moveSubscriptionY;
	TTFB_Subscription * saySubscription;
	int		   moveDirection;
	int		   moveDirectionY;
	float speechAreaScale;

	void breakJoint(Box2DSprite * _sprite);
};