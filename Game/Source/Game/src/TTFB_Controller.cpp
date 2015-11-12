#pragma once

#include <TTFB_Controller.h>
#include <StringUtils.h>

#include <iostream>

TTFB_Controller::TTFB_Controller() : Arduino("COM7"),
	lastQue(0)
{
}

void TTFB_Controller::update(Step* _step) {

	if(connected){
		// Update all components befor parsing new data
		soundButtonOne.update(_step);
		soundButtonTwo.update(_step);
		soundButtonThree.update(_step);
		soundMicSwitch.update(_step);
		lightSliderOne.update(_step);
		lightSliderTwo.update(_step);
		lightSliderThree.update(_step);
		setButtonOne.update(_step);
		setButtonTwo.update(_step);
		setButtonThree.update(_step);
		setButtonFour.update(_step);
		specialFogSwitch.update(_step);
		specialFireButton.update(_step);
		specialCurtainPot.update(_step);

		ClearCommError(this->hSerial, &this->errors, &this->status);
		int inQ = status.cbInQue;
		wchar_t * buf = new wchar_t[lastQue + 1]();
		int numRead = ReadData((char *)buf, lastQue);
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
				buffer = L"";
				auto split = StringUtils::split(current, ',');
				updateValues(split);
			}
		}
		lastQue = inQ;
		delete buf;
	}
}

void TTFB_Controller::updateValues(std::vector<std::wstring> _stringVals) {

	soundButtonOne.currentState    = (ButtonState)atoi((char *)_stringVals[(int)SOUND_BUTTON_ONE].c_str());
	soundButtonTwo.currentState    = (ButtonState)atoi((char *)_stringVals[(int)SOUND_BUTTON_TWO].c_str());
	soundButtonThree.currentState  = (ButtonState)atoi((char *)_stringVals[(int)SOUND_BUTTON_THREE].c_str());
	soundMicSwitch.currentState    = (ButtonState)atoi((char *)_stringVals[(int)SOUND_MIC_SWITCH].c_str());
	lightSliderOne.currentState    = atoi((char *)_stringVals[(int)LIGHT_SLIDER_ONE].c_str());
	lightSliderTwo.currentState    = atoi((char *)_stringVals[(int)LIGHT_SLIDER_TWO].c_str());
	lightSliderThree.currentState  = atoi((char *)_stringVals[(int)LIGHT_SLIDER_THREE].c_str());
	setButtonOne.currentState      = (ButtonState)atoi((char *)_stringVals[(int)SET_BUTTON_ONE].c_str());
	setButtonTwo.currentState      = (ButtonState)atoi((char *)_stringVals[(int)SET_BUTTON_TWO].c_str());
	setButtonThree.currentState    = (ButtonState)atoi((char *)_stringVals[(int)SET_BUTTON_THREE].c_str());
	setButtonFour.currentState     = (ButtonState)atoi((char *)_stringVals[(int)SET_BUTTON_FOUR].c_str());
	specialFogSwitch.currentState  = (ButtonState)atoi((char *)_stringVals[(int)SPECIAL_FOG_SWITCH].c_str());
	specialFireButton.currentState = (ButtonState)atoi((char *)_stringVals[(int)SPECIAL_FIRE_BUTTON].c_str());
	specialCurtainPot.currentState = atoi((char *)_stringVals[(int)SPECIAL_CURTAIN_POT].c_str());
}