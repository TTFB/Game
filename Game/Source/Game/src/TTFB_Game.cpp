#pragma once

#include <TTFB_Game.h>
#include <TTFB_MainScene.h>
#include <TTFB_MenuScene.h>
#include <TTFB_Controller.h>

TTFB_Controller * TTFB_Game::controller = new TTFB_Controller();

TTFB_Game::TTFB_Game() :
	Game(true, std::pair<std::string, Scene *>("test", nullptr), false)
{
	scenes["menuScene"] = new TTFB_MenuScene(this);
	scenes["stageScene"] = new TTFB_MainScene(this);

	switchScene("menuScene", false);
}

TTFB_Game::~TTFB_Game(){

}

void TTFB_Game::update(Step* _step) {
	controller->update(_step);
	Game::update(_step);
}