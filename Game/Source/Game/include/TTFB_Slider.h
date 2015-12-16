#pragma once

#include <node/NodeUpdatable.h>
#include <functional>

class TTFB_Slider : public NodeUpdatable {
public :
	
	int currentState;
	int lastState;

	TTFB_Slider();

	void update(Step * _step) override;

	void bind(std::function<void(int)> _bind);

	std::function<void(int)> bindFunc;
};