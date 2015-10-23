#pragma once

#include <node/NodeUpdatable.h>

enum ButtonState {
	LOW  = 0,
	HIGH = 1
};

class TTFB_Button : public NodeUpdatable {
public :
	
	ButtonState currentState;
	ButtonState lastState;

	TTFB_Button();

	void update(Step * _step) override;

	bool justUp();
	bool justDown();
};