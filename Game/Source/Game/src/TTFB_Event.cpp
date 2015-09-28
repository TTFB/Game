#pragma once

#include<TTFB_Event.h>

TTFB_Event::TTFB_Event(long _doAt, std::function<void()> _func) :
	doAt(_doAt),
	func(_func),
	funcCallCount(0),
	onCallSubscription(new TTFB_Subscription())
{
}

void TTFB_Event::call() {
	func();
	funcCallCount++;
	onCallSubscription->publish();
}

int TTFB_Event::getFuncCallCount() {
	return funcCallCount;
}

long TTFB_Event::getDoAtTime() {
	return doAt;
}

TTFB_Event::~TTFB_Event() {
	delete onCallSubscription;
}