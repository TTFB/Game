#pragma once

#include <vector>
#include <functional>

#include <node/NodeUpdatable.h>
#include <TTFB_Event.h>
#include <TTFB_Entity.h>
#include <TTFB_Expectation.h>
#include <TTFB_Whenable.h>

class TTFB_EventQueue : public TTFB_Whenable{
public:
	TTFB_EventQueue();
	~TTFB_EventQueue();

	float timeOffset;

	void update(Step * _step) override;

	TTFB_Subscription * at(float _seconds, std::function<void()> _do);
	void expectAt(float _seconds, float _leeway, std::function<bool()> _expecation, std::function<void()> _success, std::function<void()> _failure);

	float getRelativeTime();
private:
	std::vector<TTFB_Event * >  events;
	std::vector<TTFB_Expectation> expectations;
	bool firstUpdate;
};