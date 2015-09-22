#pragma once

#include <TTFB_Entity.h>

class TTFB_Actor : public TTFB_Entity {
public:
	TTFB_Actor(Shader * _shader = nullptr);
	~TTFB_Actor();
};