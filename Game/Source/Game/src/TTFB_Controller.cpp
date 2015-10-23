#pragma once

#include <TTFB_Controller.h>
#include <StringUtils.h>

#include <iostream>

TTFB_Controller::TTFB_Controller() : Arduino("COM7"),
	lastQue(0)
{
}

void TTFB_Controller::update(Step* _step) {

	// Update all components befor parsing new data
	buttonOne.update(_step);

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
			buffer = "";
			auto split = StringUtils::split(current, ',');
			updateValues(split);
		}
	}
	lastQue = inQ;
	delete buf;
}

void TTFB_Controller::updateValues(std::vector<std::string> _stringVals) {
	buttonOne.currentState = (ButtonState)atoi(_stringVals[(int)BUTTON_ONE].c_str());
}