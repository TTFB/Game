#pragma once

#include <node/NodeUpdatable.h>
#include <functional>
#include <Keyboard.h>

enum ButtonState {
	LOW  = 0,
	HIGH = 1
};

class TTFB_Button : public NodeUpdatable {
public :
	
	ButtonState currentState;
	ButtonState lastState;

	int keyboardKey;

	TTFB_Button(int _keyboardKey = -1, bool _toggle = false);

	void update(Step * _step) override;
	void bind(std::function<void(int)> _bind);

	bool justUp() const;
	bool justDown() const;

	std::function<void(int)> bindFunc;

	Keyboard * keyboard;
	bool toggle;
};