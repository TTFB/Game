#pragma once

#include <node/NodeUpdatable.h>

class TTFB_Slider : public NodeUpdatable {
public :
	
	int currentState;
	int lastState;

	TTFB_Slider();

	void update(Step * _step) override;

};