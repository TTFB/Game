#pragma once

#include <Entity.h>
#include <shader/Shader.h>

class Sprite;

class TTFB_Fog : public Entity {
public:
	
	TTFB_Fog(Shader * _shader);	
	
	void update(Step * _step) override;

private:
	Sprite * fog1;
	Sprite * fog2;
	Sprite * fog3;
	Sprite * fog4;

	bool flipDir;
};