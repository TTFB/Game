#pragma once

#include <TTFB_Slider.h>

TTFB_Slider::TTFB_Slider() :
	NodeUpdatable(),
	lastState(0),
	currentState(0)
{
}

void TTFB_Slider::update(Step* _step) {
	lastState = currentState;
}