#pragma once

#include <functional>

class TTFB_Expectation {
public:
	TTFB_Expectation(float _seconds, float _leeway, std::function<bool()> _expectation, std::function<void()> _success, std::function<void()> _failure);

	bool expectationMet();
	void success();
	void failure();
	int inTimeRange(float _time);

private:
	float highBound;
	float lowBound;
	std::function<bool()> expecationFunc;
	std::function<void()> successFunc;
	std::function<void()> failureFunc;
};
