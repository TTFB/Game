#pragma once

#include <TTFB_Controller.h>
#include <StringUtils.h>

#include <iostream>
#include <Log.h>
#include <string>
#include <glfw/glfw3.h>

TTFB_Controller::TTFB_Controller() : Arduino(""),
	lastQue(0),
	soundButtonOne(GLFW_KEY_Q),
	soundButtonTwo(GLFW_KEY_W),
	soundButtonThree(GLFW_KEY_E),
	soundMicSwitch(GLFW_KEY_R, true),
	setButtonOne(GLFW_KEY_A),
	setButtonTwo(GLFW_KEY_S),
	setButtonThree(GLFW_KEY_D),
	setButtonFour(GLFW_KEY_F)
	
{
	// Go through the COM ports looking for one with data
	// The controller is always writing so there should be something in the queue
	for(unsigned long int i = 0; i < 255; i++) {
		connect("COM" + std::to_string(i));
		if(connected){
			Sleep(2000);
			ClearCommError(this->hSerial, &this->errors, &this->status);
			if(status.cbInQue > 0) {
				break;
			}
		}
	}
}

void TTFB_Controller::update(Step* _step) {

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

	if(connected){
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
			if(posLeft != -1 && posRight > posLeft) {
				current = buffer.substr(posLeft + 1, posRight - posLeft - 1);
				buffer = "";
				auto split = StringUtils::split(current, ',');
				updateValues(split);
			}
		}
		lastQue = inQ;
		
		delete buf;
	}
}

void TTFB_Controller::updateValues(std::vector<std::string> _stringVals) {

	if(_stringVals.size() == 14){
		soundButtonOne.currentState    = (ButtonState)atoi(_stringVals[(int)SOUND_BUTTON_ONE].c_str());
		soundButtonTwo.currentState    = (ButtonState)atoi(_stringVals[(int)SOUND_BUTTON_TWO].c_str());
		soundButtonThree.currentState  = (ButtonState)atoi(_stringVals[(int)SOUND_BUTTON_THREE].c_str());
		soundMicSwitch.currentState    = (ButtonState)atoi(_stringVals[(int)SOUND_MIC_SWITCH].c_str());
		lightSliderOne.currentState    = atoi(_stringVals[(int)LIGHT_SLIDER_ONE].c_str());
		lightSliderTwo.currentState    = atoi(_stringVals[(int)LIGHT_SLIDER_TWO].c_str());
		lightSliderThree.currentState  = atoi(_stringVals[(int)LIGHT_SLIDER_THREE].c_str());
		setButtonOne.currentState      = (ButtonState)atoi(_stringVals[(int)SET_BUTTON_ONE].c_str());
		setButtonTwo.currentState      = (ButtonState)atoi(_stringVals[(int)SET_BUTTON_TWO].c_str());
		setButtonThree.currentState    = (ButtonState)atoi(_stringVals[(int)SET_BUTTON_THREE].c_str());
		setButtonFour.currentState     = (ButtonState)atoi(_stringVals[(int)SET_BUTTON_FOUR].c_str());
		specialFogSwitch.currentState  = (ButtonState)atoi(_stringVals[(int)SPECIAL_FOG_SWITCH].c_str());
		specialFireButton.currentState = (ButtonState)atoi(_stringVals[(int)SPECIAL_FIRE_BUTTON].c_str());
		specialCurtainPot.currentState = atoi(_stringVals[(int)SPECIAL_CURTAIN_POT].c_str());
	}
}

void TTFB_Controller::clearBindings() {
	soundButtonOne.bindFunc = nullptr;
	soundButtonTwo.bindFunc = nullptr;
	soundButtonThree.bindFunc = nullptr;
	soundMicSwitch.bindFunc = nullptr;
	lightSliderOne.bindFunc = nullptr;
	lightSliderTwo.bindFunc = nullptr;
	lightSliderThree.bindFunc = nullptr;
	setButtonOne.bindFunc = nullptr;
	setButtonTwo.bindFunc = nullptr;
	setButtonThree.bindFunc = nullptr;
	setButtonFour.bindFunc = nullptr;
	specialFogSwitch.bindFunc = nullptr;
	specialFireButton.bindFunc = nullptr;
	specialCurtainPot.bindFunc = nullptr;
}
