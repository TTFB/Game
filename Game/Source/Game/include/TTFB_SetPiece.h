#pragma once

#include <Box2DSprite.h>
#include <Rectangle.h>

class TTFB_SetPiece : public Box2DSprite {
public:	

	TTFB_SetPiece(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader, sweet::Rectangle _stageBounds, float _scaleMultiplier = 1.f);

	void update(Step * _step) override;

	void raise();
	void lower(float _offset = 0.0f);
	void toggle(float _offset = 0.f);

	bool isLowered() const;
	bool isRaised() const;

private:
	int  raiseDir;
	bool forceFrame;
	bool lowered;
	bool raised;
	sweet::Rectangle stageBounds;
	float offset;
};