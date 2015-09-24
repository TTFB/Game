#pragma once

#include <functional>

class TTFB_When {
public:
	std::function<bool()> when;
	std::function<void()> toDo;

	TTFB_When(std::function<bool()> _when, std::function<void()> _toDo);
};