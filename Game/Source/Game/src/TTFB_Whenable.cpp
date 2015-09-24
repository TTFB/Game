#pragma once

#include <TTFB_Whenable.h>

TTFB_Whenable::TTFB_Whenable() 
{
}

void TTFB_Whenable::when(std::function<bool()> _when, std::function<void()> _toDo) {
	whens.push_back(TTFB_When(_when, _toDo));
}
 
void TTFB_Whenable::update(Step* _step) {
	for(unsigned long int i = 0; i < whens.size(); ++i) {
		if(whens[i].when()) {
			whens[i].toDo();
			whens.erase(whens.begin() + i);
			break;
		}
	}
}