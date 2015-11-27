#pragma once

#include <TTFB_Slider.h>

TTFB_Slider::TTFB_Slider() :
	NodeUpdatable(),
	lastState(0),
	currentState(0),
	bindFunc(nullptr)
{
}

void TTFB_Slider::update(Step* _step) {
	if(bindFunc != nullptr) {
		bindFunc(currentState);
	}
	lastState = currentState;
}

void TTFB_Slider::bind(std::function<void(int)> _bind) {
	bindFunc = _bind;
}