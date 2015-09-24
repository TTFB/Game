#pragma once

#include <TTFB_When.h>

TTFB_When::TTFB_When(std::function<bool()> _when, std::function<void()> _toDo) :
	when(_when),
	toDo(_toDo)
{
}