#pragma once

#include<TTFB_EventQueue.h>

TTFB_EventQueue::TTFB_EventQueue() :
	TTFB_Whenable(),
	firstUpdate(true),
	timeOffset(0.0f)
{
}

TTFB_EventQueue::~TTFB_EventQueue() {
}

void TTFB_EventQueue::update(Step* _step) {
	if(firstUpdate) {
		timeOffset = _step->time;
		firstUpdate = false;
	}
	for(unsigned long int i = 0; i < events.size();) {
		if(events[i]->getDoAtTime() <= _step->time - timeOffset && events[i]->getFuncCallCount() == 0) {
			events[i]->call();
			events.erase(events.begin() + i);
		}else {
			i++;
		}
	}
	for(unsigned long int i = 0; i < expectations.size();) {
		if(expectations[i].inTimeRange(_step->time - timeOffset) == 0){
			if(expectations[i].expectationMet()) {
				expectations[i].success();
				expectations.erase(expectations.begin() + i);
			}else {
				i++;
			}
		}else if(expectations[i].inTimeRange(_step->time - timeOffset) == 1){
			expectations[i].failure();
			expectations.erase(expectations.begin() + i);
		}else {
			i++;
		}
	}
	TTFB_Whenable::update(_step);
}

TTFB_Subscription * TTFB_EventQueue::at(float _seconds, std::function<void()> _do) {
	TTFB_Event * ev = new TTFB_Event(_seconds, _do);
	events.push_back(ev);
	return ev->onCallSubscription;
}

void TTFB_EventQueue::expectAt(float _seconds, float _leeway, std::function<bool()> _expecation, std::function<void()> _success, std::function<void()> _failure) {
	expectations.push_back(TTFB_Expectation(_seconds, _leeway, _expecation, _success, _failure));
}