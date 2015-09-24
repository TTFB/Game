#pragma once

#include <vector>

#include <node/NodeUpdatable.h>

#include <TTFB_When.h>

class TTFB_Whenable : public virtual NodeUpdatable {
public:
	std::vector<TTFB_When> whens;
	
	TTFB_Whenable();
	
	void update(Step * _step) override;
	void when(std::function<bool()> _when, std::function<void()> _toDo);
};