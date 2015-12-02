#pragma once

#include <TTFB_Scene.h>
#include <TTFB_Game.h>
#include <TTFB_Controller.h>

TTFB_Scene::TTFB_Scene(Game* _game) :
	Scene(_game)
{
	controller = dynamic_cast<TTFB_Game *>(game)->controller;
}
