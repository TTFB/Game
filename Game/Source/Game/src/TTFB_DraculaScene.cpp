#pragma once

#include <TTFB_DraculaScene.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Stage.h>
#include <TTFB_DraculaStage.h>
#include <Box2DSprite.h>
#include <Keyboard.h>
#include <TTFB_Constants.h>
#include <TTFB_Controller.h>
#include <TTFB_SetPiece.h>

TTFB_DraculaScene::TTFB_DraculaScene(Game* _game) :
	TTFB_StageScene(_game),
	bgMusicStarted(false),
	lastFireEmission(0.0),
	clapping(nullptr)
{

#pragma region PreSetup

	setStage(new TTFB_DraculaStage(box2dWorld, baseShader));

	addAudience("L3");

	startSceneDelay = 3.0f;

	// Set pieces
	setPeiceWall1 = addSetPiece("L3_wall1", glm::vec3(10.f, 20.f, -0.5f), 1.5f);
	setPeiceWall1->raise();
	setPieceStairs = addSetPiece("L3_ramps", glm::vec3(0.f, 20.f, -0.5), 2.2f);
	setPieceStairs->raise();

#pragma  endregion 
	 
#pragma region ActorSetup

	dracula = createActor("dracula"); 
	childTransform->addChild(dracula);
	dracula->translateComponents(-12.f, dracula->getLegsOffset(), 0.f);

	TwBar * bar = stage->stageBase->firstParent()->createAntTweakBarWindow("Stage");
	stage->stageBack->firstParent()->addToAntTweakBar(bar, "Background");
	dracula->torso->firstParent()->addToAntTweakBar(bar, "Dracula");

	renfield = createActor("renfield"); 
	childTransform->addChild(renfield);
	renfield->translateComponents(-25.f, renfield->getLegsOffset(), 0.f);

#pragma endregion 

#pragma region AudioSetup

	backgroundMusic = TTFB_ResourceManager::scenario->getAudio("dracula_bg")->sound;
	backgroundMusic->setGain(0.5f);
	dialoguePlayer = new TTFB_DialoguePlayer("dracula");
	 
#pragma endregion 

#pragma region Events

	float offset = 0.0f;

	eventQueue.at(0.00f, [this]{
		countDown(startSceneDelay);
		// Test lowering wall1
		setPeiceWall1->lower();
		setPieceStairs->lower();
	});

	eventQueue.at(startSceneDelay - 5.0f, [this](){dimHouseLights();});

	eventQueue.at(0.0f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->move(-17);
		renfield->move(-19);
		dracula->say(3.0f, L"I am Dracula", true);
	});

	eventQueue.at(3.2f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.0f, L"It's really good to see you.", false);
	});

	eventQueue.at(5.2f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.f, L"I don't know what happened to the driver and my luggage and", false);
	});

	eventQueue.at(7.7f + startSceneDelay + offset, [this](){
		renfield->say(3.f, L"...well.. .with all this, I thought I was in the wrong place.", true);
	});

	eventQueue.at(10.7f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(2.3f, L"I bid you welcome", true);
	});

	// Go upstairs
	eventQueue.at(12.0f + startSceneDelay + offset, [this](){
		dracula->move(-5);
		renfield->move(-7);
		dracula->moveY(9);
		renfield->moveY(9);
	});

	eventQueue.at(13.f + startSceneDelay + offset, [this](){
		TTFB_ResourceManager::scenario->getAudio("HowlingWolf1")->sound->play();
	});

	eventQueue.at(17.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(4.5f, L"Listen to them... children of the night. What music they make!", true);
	});

	// Walking through spider web

	eventQueue.at(22.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->move(2);
		renfield->move(0);
		dracula->say(3.f, L"A spider spinning his web for the unwary fly." , false);
	});

	eventQueue.at(25.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"The blood...is the life, Mr. Renfield.", true);
	});

	eventQueue.at(28.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(1.5f, L"Why, yes.", true);
	});

	// Enter bed chamber

	eventQueue.at(30.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(4.f, L"I'm sure you will find this part of my castle more inviting.", true);
		dracula->move(10.f);
		dracula->moveY(10.f);
		renfield->move(7.f);
		renfield->moveY(10.f);
	});

	eventQueue.at(34.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(5.f, L"Oh, rather! It's quite different from outside. Oh, and the fire! It's so cheerful", true);
		renfield->move(14.f);
	});

	eventQueue.at(39.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"I didn't know but that you might be hungry.", true);
	});

	eventQueue.at(42.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Thank you. That's very kind of you. But I'm a bit worried about my luggage", false);
	});

	eventQueue.at(45.f + startSceneDelay + offset, [this](){
		renfield->say(2.5f, L"You see, all your papers were in...", true);
	});

	eventQueue.at(47.5f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(4.5f, L"I took the liberty of having your luggage brought up. Allow me.", true);
	});

	eventQueue.at(51.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.f, L"Oh, yes. Thanks", true);
	});

	eventQueue.at(53.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.5f, L"I trust you have kept your coming here...a secret?", true);
	});

	eventQueue.at(56.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"I've followed your instructions implicitly.", true);
	});

	eventQueue.at(59.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(2.f, L"Excellent, Mr. Renfield, excellent.", false);
	});

	eventQueue.at(61.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(5.f, L"And now, if you're not too fatiqued I would like to discuss the lease on Carfax Abbey", true);
	});

	eventQueue.at(66.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(4.f, L"Oh, yes. Everything is in order, awaiting your signature. Here is the lease.", false);
	});

	eventQueue.at(68.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
	});

	eventQueue.at(70.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(4.f, L"I hope I've brought enough labels for your luggage", true);
	});

	eventQueue.at(74.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(4.f, L"I am taking with me only three...boxes.", true);
	});

	eventQueue.at(78.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.f, L"Very well", true);
	});

	eventQueue.at(80.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(6.f, L"I have chartered a ship to take us to England. We will be leaving... tomorrow... evening.", true);
	});

	eventQueue.at(86.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.f, L"Everything will be ready", true);
	});

	eventQueue.at(87.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		// Pointing to bed
		dracula->say(3.f, L"I hope you will find this comfortable", true);
	});

	eventQueue.at(90.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Thanks. It looks very inviting", true);
	});

	// Renfield cuts his finger
	
	eventQueue.at(93.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(2.f, L"Ouch!", true);
	});

	// Dracula stealthly approaches Renfield

	// Renfields crucifix falls over the cut finger

	// Dracula turns away

	eventQueue.at(95.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(5.f, L"Oh, it's nothing serious. Just a small cut from that paperclip. It's just a scratch.!", true);
	});
	
	eventQueue.at(100.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		// Pours glass of wine
		dracula->say(4.f, L"This...is very old wine. I hope you will like it.", true);
	});

	eventQueue.at(104.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Aren't you drinking?", true);
	});

	eventQueue.at(107.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"I never drink... wine", true);
	});

	eventQueue.at(110.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Well, it's delicous", true);
	});

	eventQueue.at(113.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"And, now, I'll leave you.", true);
	});

	eventQueue.at(116.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Well, good night.", true);
	});

	eventQueue.at(119.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"Good night, Mr. Renfield.", true);
	});

	// Dracula leaves
	// Bat flies through window

#pragma  endregion 

#pragma region Expectations 

	// Add expectations here

#pragma endregion 

#pragma region ControllerSetup

	controller->lightSliderOne.bind([this](int _value){
		lights[1]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
	});

	controller->lightSliderTwo.bind([this](int _value){
		lights[2]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
	});

	controller->lightSliderThree.bind([this](int _value){
		lights[3]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
	});

	controller->setButtonOne.bind([this](int _value) {
		if(controller->setButtonOne.justDown()) {
		}
	});
	
	// Move this into stage scene
	controller->specialCurtainPot.bind([this](int _value){
		float increase = _value / 30.0f;
		glm::vec3 leftTrans = stage->curtainLeft->firstParent()->getTranslationVector();
		glm::vec3 rightTrans = stage->curtainRight->firstParent()->getTranslationVector();
		leftTrans.x  = (-increase - 12);
		rightTrans.x = (increase + 12);
		stage->curtainLeft->firstParent()->translate(leftTrans, false);
		stage->curtainRight->firstParent()->translate(rightTrans, false);
		//-46 is open, -12 is closed for left curtain
	});

	controller->specialFogSwitch.bind([this](int _value) {
		if(controller->specialFogSwitch.justDown() || controller->specialFogSwitch.justUp()) {
			toggleFog();
		}
	});

	controller->soundMicSwitch.bind([this](int _value) {
		if(_value == 1) {
			dialoguePlayer->unmute();
		}else {
			dialoguePlayer->mute();
		}
	});

#pragma endregion 

#pragma region AdditionalSceneSetup

	addFog();

#pragma endregion 	

}

TTFB_DraculaScene::~TTFB_DraculaScene() {
	if(clapping != nullptr) {
		clapping->stop();
	}
	delete dialoguePlayer;
}

void TTFB_DraculaScene::update(Step* _step) {
	if(!bgMusicStarted) {
		backgroundMusic->play();
		bgMusicStarted = true;
	}
	
	if(keyboard->keyDown(GLFW_KEY_K)) {
		eventQueue.timeOffset += 0.01f;
	}

	if(!sceneEnded){
		eventQueue.update(_step);
	}

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

void TTFB_DraculaScene::endScene() {
	dialoguePlayer->playing = false;
	backgroundMusic->stop();
	if(score <= ONE_STAR){
		TTFB_StageScene::endScene(DRACULA, DRACULA, "lose", "TryAgain");
	}else {
		TTFB_StageScene::endScene(DRACULA, MENU, "draculaWin", "Ending"); // Add in sound effect
	}
}
