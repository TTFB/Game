#pragma once

#include <TTFB_Button.h>
#include <Keyboard.h>

TTFB_Button::TTFB_Button(int _keyboardKey, bool _toggle) :
	NodeUpdatable(),
	currentState(LOW),
	lastState(LOW),
	keyboardKey(_keyboardKey),
	bindFunc(nullptr),
	keyboard(&Keyboard::getInstance()),
	toggle(_toggle)
{
}

bool TTFB_Button::justUp() const {
	return (currentState == LOW && lastState == HIGH) || keyboardKey != -1 && (keyboard->keyJustUp(keyboardKey));
}

bool TTFB_Button::justDown() const {
	return (currentState == HIGH && lastState == LOW) || keyboardKey != -1 && (keyboard->keyJustDown(keyboardKey));
}

void TTFB_Button::update(Step * _step) {
	if(toggle) {
		if(keyboard->keyJustUp(keyboardKey)) {
			currentState = currentState == LOW ? HIGH : LOW;
		}
	}

	if(bindFunc != nullptr){
		bindFunc(static_cast<int>(currentState));
	}
	lastState = currentState;
}

void TTFB_Button::bind(std::function<void(int)> _bind) {
	bindFunc = _bind;
}