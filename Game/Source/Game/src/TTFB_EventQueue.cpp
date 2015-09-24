#pragma once

#include<TTFB_EventQueue.h>

TTFB_EventQueue::TTFB_EventQueue() {
}

TTFB_EventQueue::~TTFB_EventQueue() {
}

void TTFB_EventQueue::update(Step* _step) {
	for(auto event : events) {
		if(event->getDoAtTime() <= _step->time && event->getFuncCallCount() == 0) {
			event->call();
		}
	}
}

void TTFB_EventQueue::at(long _seconds, std::function<void()> _do) {
	events.push_back(new TTFB_Event(_seconds, _do));
}