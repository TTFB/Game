#pragma once

#include <TTFB_DraculaScene.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Stage.h>

TTFB_DraculaScene::TTFB_DraculaScene(Game* _game) :
	TTFB_StageScene(_game, 100.0f, "L1_Floor", "L3_RightWall", "L1_Background", "L3_Top", "L3_Bottom"),
	bgMusicStarted(false),
	lastFireEmission(0.0)
{

#pragma region PreSetup

	startSceneDelay = 3.0f;

#pragma  endregion 

#pragma region ActorSetup

	dracula = createActor("dracula"); 
	childTransform->addChild(dracula);
	dracula->translateComponents(-20.f, dracula->getLegsOffset(), 0.f);

	renfeild = createActor("renfield"); 
	childTransform->addChild(renfeild);
	renfeild->translateComponents(20.f, renfeild->getLegsOffset(), 0.f);

#pragma endregion 

#pragma region AudioSetup

	backgroundMusic = TTFB_ResourceManager::scenario->getAudio("dracula_bg")->sound;
	backgroundMusic->setGain(0.5f);
	dialoguePlayer = new TTFB_DialoguePlayer("dracula");
	 
#pragma endregion 

#pragma region Events

	eventQueue.at(startSceneDelay - 5.0f, [this](){dimHouseLights();});

	eventQueue.at(0.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.0f, L"I am Dracula", false);
		decScore(400);
	});

	eventQueue.at(4.0f + startSceneDelay, [this](){
		incScore(400);
	});

	eventQueue.at(8.0f + startSceneDelay, [this](){
		incScore(400);
	});

#pragma  endregion 

#pragma region Expectations 

	// Add expectations here

#pragma endregion 

#pragma region ControllerSetup

	// Add controller bindings here

#pragma endregion 

#pragma region AdditionalSceneSetup

	addFog();

#pragma endregion 
}

TTFB_DraculaScene::~TTFB_DraculaScene() {
}

void TTFB_DraculaScene::update(Step* _step) {
	if(!bgMusicStarted) {
		backgroundMusic->play();
		bgMusicStarted = true;
	}

	eventQueue.update(_step);

	TTFB_StageScene::update(_step);
}

void TTFB_DraculaScene::render(sweet::MatrixStack* _matrixStack, RenderOptions* _renderOptions) {

	TTFB_StageScene::render(_matrixStack, _renderOptions);
}

void TTFB_DraculaScene::load() {

	TTFB_StageScene::load();
}

void TTFB_DraculaScene::unload() {
	
	TTFB_StageScene::unload();
}