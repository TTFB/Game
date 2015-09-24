#pragma once

#include <TTFB_Entity.h>
#include <Animation.h>
#include <Box2DSprite.h>

class TTFB_Actor : public Box2DSprite {
public:
	TTFB_Actor(Box2DWorld * _world, Shader * _shader = nullptr);
	~TTFB_Actor();

	virtual void update(Step * _step) override;
	void move(float _moveBy);

private:
	Animation<float> moveAnimations;
	float moveVal;
};