#pragma once

#include <TTFB_Controller.h>
#include <StringUtils.h>

#include <iostream>

TTFB_Controller::TTFB_Controller() : Arduino("COM7"),
	lastQue(0)
{
}

void TTFB_Controller::update(Step* _step) {
	ClearCommError(this->hSerial, &this->errors, &this->status);
	int inQ = status.cbInQue;
	char * buf = new char[lastQue + 1]();
	int numRead = ReadData(buf, lastQue);
	buf[lastQue] = '\0';
	if(numRead > 0){
		int posLeft  = -1;
		int posRight = -1;
		for(int i = lastQue; i >= 0; i--) {
			if(buf[i] == ']' && posLeft == -1) {
				posRight = i;
			}
			if(buf[i] == '[' && posRight > 0) {
				posLeft = i;
				break;
			}
		}
		buffer += buf;
		if(posLeft != -1 && posRight != -1) {
			current = buffer.substr(posLeft + 1, posRight - posLeft - 1);
			std::cout << current << "\n"; 
			buffer = "";
			auto split = StringUtils::split(current, ',');
		}
	}
	lastQue = inQ;
	delete buf;
}