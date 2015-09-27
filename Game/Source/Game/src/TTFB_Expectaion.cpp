#pragma once

#include <TTFB_Expectation.h>

TTFB_Expectation::TTFB_Expectation(float _seconds, float _leeway, std::function<bool()> _expectation, std::function<void()> _success, std::function<void()> _failure) :
	expecationFunc(_expectation),
	successFunc(_success),
	failureFunc(_failure),
	highBound(_seconds + _leeway),
	lowBound(_seconds - _leeway)
{
}

bool TTFB_Expectation::expectationMet() {
	return expecationFunc();
}

void TTFB_Expectation::success() {
	successFunc();
}

void TTFB_Expectation::failure() {
	failureFunc();
}

int TTFB_Expectation::inTimeRange(float _time) {
	 if(_time >= lowBound && _time <= highBound) {
		 return 0;
	 }else if(_time < lowBound) {
		 return -1;
	 }else {
		 return 1;
	 }
}