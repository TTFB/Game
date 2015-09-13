#pragma once

#include <TTFB_Game.h>
#include <TTFB_MainScene.h>

TTFB_Game::TTFB_Game() :
	Game(true, std::pair<std::string, Scene *>("test", new TTFB_MainScene(this)), false)
{
}

TTFB_Game::~TTFB_Game(){

}