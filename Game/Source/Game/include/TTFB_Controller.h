#pragma once

#include <Arduino.h>

#include <string>

#include <TTFB_Button.h>
#include <TTFB_Slider.h>

enum ControllerMapping {
	SOUND_BUTTON_ONE    = 0,
	SOUND_BUTTON_TWO    = 1,
	SOUND_BUTTON_THREE  = 2,
	SOUND_MIC_SWITCH    = 3,
	LIGHT_SLIDER_ONE    = 4,
	LIGHT_SLIDER_TWO    = 5,
	LIGHT_SLIDER_THREE  = 6,
	SET_BUTTON_ONE      = 7,
	SET_BUTTON_TWO      = 8,
	SET_BUTTON_THREE    = 9,
	SET_BUTTON_FOUR     = 10,
	SPECIAL_FOG_SWITCH  = 11,
	SPECIAL_FIRE_BUTTON = 12,
	SPECIAL_CURTAIN_POT = 13
};

class TTFB_Controller : public Arduino {
public:	

	int lastQue;
	std::string buffer;
	std::string current;

	TTFB_Button soundButtonOne;
	TTFB_Button soundButtonTwo;
	TTFB_Button soundButtonThree;
	TTFB_Button soundMicSwitch;
	TTFB_Slider lightSliderOne;
	TTFB_Slider lightSliderTwo;
	TTFB_Slider lightSliderThree;
	TTFB_Button setButtonOne;
	TTFB_Button setButtonTwo;
	TTFB_Button setButtonThree;
	TTFB_Button setButtonFour;
	TTFB_Button specialFogSwitch;
	TTFB_Button specialFireButton;
	TTFB_Slider specialCurtainPot;

	TTFB_Controller();

	void update(Step * _step) override;
	void updateValues(std::vector<std::string> _stringVals);
	void clearBindings();
};