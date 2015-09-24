#pragma once

#include <vector>
#include <functional>

#include <node/NodeUpdatable.h>
#include <TTFB_Event.h>
#include <TTFB_Entity.h>

class TTFB_EventQueue : NodeUpdatable{
public:
	TTFB_EventQueue();
	~TTFB_EventQueue();

	void update(Step * _step) override;

	void at(long _seconds, std::function<void()> _do);

private:
	std::vector<TTFB_Event *> events;
};