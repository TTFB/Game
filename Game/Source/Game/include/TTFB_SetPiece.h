#pragma once

#include <Box2DSprite.h>

class TTFB_SetPiece : public Box2DSprite {
public:	

	TTFB_SetPiece(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader);

	void update(Step * _step) override;

	void raise();
	void lower();

private:
	int raiseDir;
};