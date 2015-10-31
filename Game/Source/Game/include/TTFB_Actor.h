#pragma once

#include <Box2DSuperSprite.h>
#include <TTFB_Whenable.h>

#include <string>

class TextArea;
class BulletWorld;
class Scene;
class Font;
class TTFB_Subscription;

enum Category {
	BOUNDARY =          0x0001,
    ACTOR	 =          0x0002,
    //ENEMY_SHIP =        0x0004,
    //FRIENDLY_AIRCRAFT = 0x0008,
    //ENEMY_AIRCRAFT =    0x0010,
};

class TTFB_Actor : public Box2DSuperSprite, public TTFB_Whenable{
public:
	TTFB_Actor(Box2DWorld * _world, BulletWorld * _bulletWorld, Scene * _scene, Font * _font, Shader * _textShader, Shader * _shader = nullptr);
	~TTFB_Actor();

	virtual void update(Step * _step) override;
	
	virtual TTFB_Subscription * move(float _moveBy);
	virtual TTFB_Subscription * say(float _durationSeconds, std::wstring _say, bool _hideOnComplete);
	virtual void flip();

private:
	Box2DSprite * torso;
	Box2DSprite * head;
	Box2DSprite * leftArm;
	Box2DSprite * rightArm;
	Box2DSprite * legs;

	TextArea * speechArea; 
	TTFB_Subscription * moveSubscription;
	TTFB_Subscription * saySubscription;
	int		   moveDirection;
	float speechAreaScale;
};