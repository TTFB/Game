#pragma once

#include <TTFB_Button.h>

TTFB_Button::TTFB_Button() :
	NodeUpdatable(),
	currentState(LOW),
	lastState(LOW)
{
}

bool TTFB_Button::justUp() {
	return currentState == LOW && lastState == HIGH;
}

bool TTFB_Button::justDown() {
	return currentState == HIGH && lastState == LOW;
}

void TTFB_Button::update(Step* _step) {
	lastState = currentState;
}