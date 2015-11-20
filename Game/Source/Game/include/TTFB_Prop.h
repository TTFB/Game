#pragma once

#include <Box2DSprite.h>

class TTFB_Prop : public Box2DSprite{
public:

	TTFB_Prop(Box2DWorld * _world, std::string _samplerResourceId, Shader * _shader = nullptr);
	
};