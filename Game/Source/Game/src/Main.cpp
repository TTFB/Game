#pragma once

#include <Vox.h>
#include <node\Node.h>
#include <typeinfo>
#include <Texture.h>
#include <Game.h>
#include <TTFB_ResourceManager.h>
#include <Log.h>

#include <TTFB_Game.h>

#ifdef _DEBUG
	// memory leak debugging
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main(void){
#ifdef _DEBUG
	_CrtMemState s1;
	_CrtMemCheckpoint( &s1 );
#endif

	Log::THROW_ON_ERROR = true;

	vox::initialize("Game");
	TTFB_ResourceManager::init();
	TTFB_ResourceManager::load();
	TTFB_Game * game = new TTFB_Game();

	while (game->isRunning){
		game->performGameLoop();
	}
	
	delete game;
	game = nullptr;
	TTFB_ResourceManager::destruct();
#ifdef _DEBUG
	std::cout << "Final node count: " << Node::nodes.size() << std::endl;

	for(auto n : Node::nodes){
		std::cout << typeid(*n).name() << " " << n << std::endl;
	}
#endif

	vox::destruct();
	
#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&s1);
#endif
}