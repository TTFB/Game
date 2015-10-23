#pragma once

#include <TTFB_Game.h>
#include <TTFB_MainScene.h>
#include <TTFB_MenuScene.h>

TTFB_Game::TTFB_Game() :
	Game(true, std::pair<std::string, Scene *>("test", new TTFB_MenuScene(this)), false)
{
	scenes["stageScene"] = new TTFB_MainScene(this);
}

TTFB_Game::~TTFB_Game(){

}