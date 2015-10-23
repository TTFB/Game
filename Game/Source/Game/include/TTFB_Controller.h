#pragma once

#include <Arduino.h>

#include <string>

#include <TTFB_Button.h>

enum ControllerMapping {
	BUTTON_ONE = 0
};

class TTFB_Controller : public Arduino {
public:	
	int lastQue;
	std::string buffer;
	std::string current;

	TTFB_Button buttonOne;

	TTFB_Controller();

	void update(Step * _step) override;
	void updateValues(std::vector<std::string> _stringVals);
};