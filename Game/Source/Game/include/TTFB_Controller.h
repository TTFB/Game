#pragma once

#include <Arduino.h>

#include <string>

class TTFB_Controller : public Arduino {
public:	
	int lastQue;
	std::string buffer;
	std::string current;

	TTFB_Controller();

	void update(Step * _step) override;
};