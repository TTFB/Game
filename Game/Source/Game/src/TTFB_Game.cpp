#pragma once

#include <TTFB_Game.h>
#include <TTFB_SpamalotScene.h>
#include <TTFB_MenuScene.h>
#include <TTFB_Controller.h>
#include <TTFB_DraculaScene.h>
#include <AntTweakBar.h>
#include <Keyboard.h>
#include <TTFB_Constants.h>

int myVar = 5;

TTFB_Game::TTFB_Game() :
	Game(true, std::pair<std::string, Scene *>("test", nullptr), false),
	controller(nullptr)
{
	controller = new TTFB_Controller();
	controller->update(&sweet::step);

	scenes["menu"]  = new TTFB_MenuScene(this);
	scenes["dracula"] = new TTFB_DraculaScene(this);
	scenes["spamalot"]  = new TTFB_SpamalotScene(this);
	scenes["temp"]  = new Scene(this);
	
	switchScene("menu", false);
}

TTFB_Game::~TTFB_Game(){
	scenes.clear();
}

void TTFB_Game::update(Step* _step) {
	
if(keyboard->keyJustUp(GLFW_KEY_3)) {
		sweet::toggleAntTweakBar();
	}

	controller->update(_step);
	Game::update(_step);
}

void TTFB_Game::draw() {
	Game::draw();
}

void TTFB_Game::switchToScene(std::string _scene) {
	if(_scene == DRACULA) {
 		delete currentScene;
 		currentScene = nullptr;
 		scenes.erase("dracula");
 		scenes["dracula"] = new TTFB_DraculaScene(this);
 		switchScene("dracula", false);
 	}else if(_scene == SPAMALOT) {
 		delete currentScene;
 		currentScene = nullptr;
 		scenes.erase("spamalot");
 		scenes["spamalot"] = new TTFB_SpamalotScene(this);
 		switchScene("spamalot", false);
 	}else if(_scene == MENU) {
 		delete currentScene;
 		currentScene = nullptr;
 		scenes.erase("menu");
 		scenes["menu"] = new TTFB_MenuScene(this);
 		switchScene("menu", false);
 	}
}
