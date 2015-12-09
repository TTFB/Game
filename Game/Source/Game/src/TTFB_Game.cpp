#pragma once

#include <TTFB_Game.h>
#include <TTFB_SpamalotScene.h>
#include <TTFB_MenuScene.h>
#include <TTFB_Controller.h>
#include <TTFB_DraculaScene.h>

TTFB_Game::TTFB_Game() :
	Game(true, std::pair<std::string, Scene *>("test", nullptr), false),
	controller(nullptr)
{
	controller = new TTFB_Controller();
	controller->update(&sweet::step);

	scenes["menuScene"]  = new TTFB_MenuScene(this);
	scenes["spamalot"] = new TTFB_SpamalotScene(this);
	scenes["dracula"]    = new TTFB_DraculaScene(this);
 
	switchScene("menuScene", false);
}

TTFB_Game::~TTFB_Game(){

}

void TTFB_Game::update(Step* _step) {
	controller->update(_step);
	Game::update(_step);
}