#pragma once

#include <TTFB_Button.h>

TTFB_Button::TTFB_Button() :
	NodeUpdatable(),
	currentState(LOW),
	lastState(LOW),
	bindFunc(nullptr)
{
}

bool TTFB_Button::justUp() {
	return currentState == LOW && lastState == HIGH;
}

bool TTFB_Button::justDown() {
	return currentState == HIGH && lastState == LOW;
}

void TTFB_Button::update(Step* _step) {
	if(bindFunc != nullptr){
		bindFunc((int)currentState);
	}
	lastState = currentState;
}

void TTFB_Button::bind(std::function<void(int)> _bind) {
	bindFunc = _bind;
}