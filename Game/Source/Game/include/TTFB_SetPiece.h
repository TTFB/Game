#pragma once

#include <Box2DSprite.h>
#include <Rectangle.h>

class TTFB_SetPiece : public Box2DSprite {
public:	

	TTFB_SetPiece(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader, sweet::Rectangle _stageBounds);

	void update(Step * _step) override;

	void raise();
	void lower();
	void toggle();

	bool isLowered();
	bool isRaised();

private:
	int raiseDir;
	bool forceFrame;
	bool lowered;
	bool raised;
	sweet::Rectangle stageBounds;
};