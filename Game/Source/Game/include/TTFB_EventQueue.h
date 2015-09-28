#pragma once

#include <vector>
#include <functional>

#include <node/NodeUpdatable.h>
#include <TTFB_Event.h>
#include <TTFB_Entity.h>
#include <TTFB_Expectation.h>

class TTFB_EventQueue : NodeUpdatable{
public:
	TTFB_EventQueue();
	~TTFB_EventQueue();

	void update(Step * _step) override;

	TTFB_Subscription * at(float _seconds, std::function<void()> _do);
	void expectAt(float _seconds, float _leeway, std::function<bool()> _expecation, std::function<void()> _success, std::function<void()> _failure);

private:
	std::vector<TTFB_Event * >  events;
	std::vector<TTFB_Expectation> expectations;
};