#pragma once

#include <Game.h>

class TTFB_Controller;

class TTFB_Game : public Game{
public:

	TTFB_Controller * controller;

	TTFB_Game();
	~TTFB_Game();

	void update(Step * _step) override;
	void draw() override;

	void switchToScene(std::string _scene);

	enum BOX2D_CATEGORY{
		kBOUNDARY = 0x0001,
		kPLAYER = 0x0002,
		kBUMPER = 0x0004,
		kENEMY = 0x0008,
		kDEAD_ZONE = 0x00010,
		kMONSTER = 0x00020,
		kCAT7 = 0x00040,
		kCAT8 = 0x00080,
		kCAT9 = 0x00100,
		kCAT10 = 0x00200,
		kCAT11 = 0x00400,
		kCAT12 = 0x00800
	};
};