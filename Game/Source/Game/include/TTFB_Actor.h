#pragma once

#include <Box2DSprite.h>
#include <TTFB_Whenable.h>

#include <string>

class TextArea;
class BulletWorld;
class Scene;
class Font;

class TTFB_Actor : public Box2DSprite, public TTFB_Whenable{
public:
	TTFB_Actor(Box2DWorld * _world, BulletWorld * _bulletWorld, Scene * _scene, Font * _font, Shader * _textShader, Shader * _shader = nullptr);
	~TTFB_Actor();

	virtual void update(Step * _step) override;
	
	void move(float _moveBy);
	void  say(float _durationSeconds, std::wstring _say);

private:
	TextArea * speechArea; 
	int		   moveDirection;
};