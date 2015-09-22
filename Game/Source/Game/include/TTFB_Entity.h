#pragma once

#include <Sprite.h>

class TTFB_Entity : public Sprite {
public:
	TTFB_Entity(Shader * _shader = nullptr);
	~TTFB_Entity();
}; 