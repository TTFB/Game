#pragma once

#include <TTFB_Stage.h>

class TTFB_DraculaStage : public TTFB_Stage {
public:	
	TTFB_DraculaStage(Box2DWorld * _world, Shader * _shader);
};