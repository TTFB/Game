#pragma once

#include <node/NodeUpdatable.h>
#include <functional>

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
	void bind(std::function<void(int)> _bind);

	bool justUp();
	bool justDown();

	std::function<void(int)> bindFunc;
};