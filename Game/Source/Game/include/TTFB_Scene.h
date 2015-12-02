#pragma once
#include <Scene.h>

class TTFB_Controller;

class TTFB_Scene : public Scene {
public:	
	TTFB_Controller * controller;
	TTFB_Scene(Game * _game);
};