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
#include <TTFB_Prop.h>
#include <ParticleSystem.h>

#define FORCE_ACTIONS true

TTFB_DraculaScene::TTFB_DraculaScene(Game* _game) :
	TTFB_StageScene(_game),
	clapping(nullptr),
	lastFireEmission(0.0),
	bgMusicStarted(false)
{

#pragma region PreSetup

	setStage(new TTFB_DraculaStage(box2dWorld, baseShader));

	addAudience("L3");

	startSceneDelay = 10.0f;

	// Set pieces
	setPeiceBuilding = addSetPiece("L3_MainBuilding", glm::vec3(3.f, 20.f, -0.5f), 2.5f);
	setPeiceBuilding->raise();
	setPeiceBuilding->lower();

	//setPeiceBuildingForeground= addSetPiece("L3_BuildingForeground", glm::vec3(3.f, 20.f, -0.5f), 2.5f);
	//setPeiceBuildingForeground->raise();
	setPieceWeb = addSetPiece("L3_spiderWeb2", glm::vec3(-2.f, 25.f, -0.5f), 1.0f);
	setPieceWeb->raise();
	setPieceBed = addSetPiece("L3_Bed", glm::vec3(20.f, 20.f, -0.5f), 0.2f);
	setPieceBed->raise();
	
	setPieceFireplace = addSetPiece("L3_Fireplace", glm::vec3(15.f, 20.f, -0.5f), 0.3f);
	setPieceFireplace->raise();
	
	setPieceLuggage = addSetPiece("L3_Luggage", glm::vec3(5.f, 20.f, -0.5f), 0.5f);
	setPieceLuggage->raise();
	
	setPieceLease = addSetPiece("L3_Lease", glm::vec3(15.f, 20.f, -0.5f), 0.3f);
	setPieceLease->raise();

	//sound conditions
	conditions["wolfCallPlayed"] = false; //holds like a bool
	conditions["draculaSoundPlayed"] = false;
	conditions["boxSound1Played"] = false;
	conditions["boxSound2Played"] = false;
	conditions["boxSound3Played"] = false;
	conditions["paperCutSoundPlayed"] = false;
	conditions["wineSoundPlayed"] = false;
	conditions["doorSoundPlayed"] = false;
	conditions["batSoundPlayed"] = false;
	conditions["faintSoundPlayed"] = false;

	wineProp = addProp("L3_wineBottle", glm::vec3(-8, 10, 0.f), 0.5f);
	wineProp->setVisible(false);

	lease = addProp("L3_Lease", glm::vec3(-8, 10, 0.f), 0.5f);
	lease->setVisible(false);

#pragma  endregion 
	 
#pragma region ActorSetup

	dracula = createActor("dracula"); 
	childTransform->addChild(dracula);
	dracula->translateComponents(-12.f, dracula->getLegsOffset(), 0.f);

	TwBar * bar = stage->stageBase->firstParent()->createAntTweakBarWindow("Stage");
	stage->stageBack->firstParent()->addToAntTweakBar(bar, "Background");
	dracula->torso->firstParent()->addToAntTweakBar(bar, "Dracula");
	dracula->pickupPropLeft(wineProp);

	renfield = createActor("renfield"); 
	childTransform->addChild(renfield);
	renfield->translateComponents(-25.f, renfield->getLegsOffset(), 0.f);
	renfield->pickupPropRight(lease);

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
	});

	eventQueue.at(startSceneDelay - 5.0f, [this](){dimHouseLights();});

	eventQueue.at(0.0f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->move(-17);
		renfield->move(-19);
		dracula->flip();
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
		dracula->flip();
		dracula->moveY(11.7);
		renfield->moveY(11.7);
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
		dracula->say(3.f, L"A spider spinning his web for the unwary fly.", false);
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
		renfield->move(7.f);
	});

	eventQueue.at(34.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(5.f, L"Oh, rather! It's quite different from outside. Oh, and the fire! It's so cheerful", true);
		renfield->move(14.f);
	});

	eventQueue.at(39.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"I didn't know but that you might be hungry.", true);
		renfield->flip();
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
		renfield->applyImpulseLeftArm(0.f, 5.f);
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
		dracula->applyImpulseLeftArm(0.f, 5.f);
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
		wineProp->setVisible(true);
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
		wineProp->setVisible(false);
	});

	eventQueue.at(116.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		renfield->say(3.f, L"Well, good night.", true);
	});

	eventQueue.at(119.f + startSceneDelay + offset, [this](){
		dialoguePlayer->playNext();
		dracula->say(3.f, L"Good night, Mr. Renfield.", true);
	});

	eventQueue.at(121.f + startSceneDelay + offset, [this](){
		dracula->flip();
		dracula->move(-35.f);
	});

	eventQueue.at(129.f + startSceneDelay + offset, [this](){
		dracula->moveY(7.3f);
	});

	eventQueue.at(142.f + startSceneDelay + offset, [this](){
		clapping = TTFB_ResourceManager::scenario->getAudio("clapping1")->sound;
		clapping->setGain(0.8f);
		clapping->play();
		endScene();
	});

	// Dracula leaves
	// Bat flies through window

#pragma  endregion 

#pragma region Expectations 

	//scene setup
	eventQueue.expectAt(startSceneDelay + offset, 3.f, 
		[this](){return !dialoguePlayer->muted;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(startSceneDelay + offset, 3.f, 
		[this](){return lights[1]->getIntensities().r > 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(startSceneDelay + offset, 3.f, 
		[this](){return stage->curtainLeft->firstParent()->getTranslationVector().x < -44.0f;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(22.f, 4.f, 
		[this](){return setPeiceBuilding->isLowered();},
		[this](){incScore();}, 
		[this](){decScore();});
	//need to drop set pieces
	//fog ON
	eventQueue.expectAt(0.0f + startSceneDelay+ offset, 2.f, 
		[this](){return fogActive == true;},
			[this](){incScore();}, 
			[this](){decScore();});
	//dracula enters sound effect
	eventQueue.expectAt(2.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["draculaSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//blue Light dim (outside) to 30%
	eventQueue.expectAt(11.5f + startSceneDelay + offset, 3.f, 
		[this](){return lights[1]->getIntensities().r > 0.2 && lights[1]->getIntensities().r < 1.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	//red Light full (inside)
	eventQueue.expectAt(11.5f + startSceneDelay + offset, 3.f, 
		[this](){return lights[2]->getIntensities().r > 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	//wolf call
	eventQueue.expectAt(14.0f + offset + startSceneDelay, 4.f, 
		[this](){return conditions["wolfCallPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//spider web set
	eventQueue.expectAt(22.f, 4.f, 
		[this](){return setPieceWeb->isLowered();},
		[this](){incScore();}, 
		[this](){decScore();});
	//lights 3 30%
	eventQueue.expectAt(29.0f + offset + startSceneDelay, 2.f, 
		[this](){return lights[3]->getIntensities().r > 0.2 && lights[3]->getIntensities().r < 1.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	//bedroom interior set
	eventQueue.expectAt(30.f, 4.f, 
		[this](){return setPieceBed->isLowered();},
		[this](){incScore();}, 
		[this](){decScore();});
	//fog OFF
	eventQueue.expectAt(34.0f + startSceneDelay+ offset, 3.f, 
		[this](){return fogActive == false;},
			[this](){incScore();}, 
			[this](){decScore();});
	//fire ON
	eventQueue.expectAt(35.0f + startSceneDelay+ offset, 3.f, 
		[this](){return fireActive == true;},
			[this](){incScore();}, 
			[this](){decScore();});
	//luggage placed set
	//lights 70% (red, inside)
	eventQueue.expectAt(53.0f + startSceneDelay + offset, 3.f, 
		[this](){return lights[2]->getIntensities().r > 0.2 && lights[2]->getIntensities().r < 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	//lease appears set
	eventQueue.expectAt(66.0f + startSceneDelay+ offset, 3.f, 
	[this](){return lease->isVisible() == true;},
			[this](){incScore();}, 
			[this](){decScore();});
	//knocking sound set (boxes)
	eventQueue.expectAt(75.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["boxSound1Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(75.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["boxSound2Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(75.0f + offset + startSceneDelay, 3.f, 
		[this](){return conditions["boxSound3Played"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//lights 3 100%
	eventQueue.expectAt(86.0f + offset + startSceneDelay, 2.f, 
		[this](){return lights[3]->getIntensities().r > 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});

	//lights 2 50%
	eventQueue.expectAt(86.0f + offset + startSceneDelay, 2.f, 
		[this](){return lights[2]->getIntensities().r > 0.5f && lights[2]->getIntensities().r < 3.2f;},
			[this](){incScore();}, 
			[this](){decScore();});

	//paperclup cut sound effect
	eventQueue.expectAt(92.0f + offset + startSceneDelay, 4.f, 
		[this](){return conditions["paperCutSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//pouring wine sound effect
	eventQueue.expectAt(100.0f + offset + startSceneDelay, 3.f, 
		[this](){return conditions["wineSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//dracula leaving sound effeect (think closing door? exit stage left)
	eventQueue.expectAt(130.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["doorSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//bats sound effect
	eventQueue.expectAt(132.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["batSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//renfield fainting sound effect
	eventQueue.expectAt(133.0f + offset + startSceneDelay, 2.f, 
		[this](){return conditions["faintSoundPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});

	//mic off
	eventQueue.expectAt(135.0f + offset + startSceneDelay, 5.f, 
		[this](){return dialoguePlayer->muted;},
			[this](){incScore();}, 
			[this](){decScore();});

	//curtain close
	eventQueue.expectAt(135.0f + offset + startSceneDelay, 5.f, 
		[this](){return stage->curtainLeft->firstParent()->getTranslationVector().x < -5.0f;},
			[this](){incScore();}, 
			[this](){decScore();});
	
	//lights off
	eventQueue.expectAt(135.0f + offset + startSceneDelay, 5.f, 
		[this](){return lights[3]->getIntensities().r < 0.2;},
			[this](){incScore();}, 
			[this](){decScore();;});
	eventQueue.expectAt(135.0f + offset + startSceneDelay, 5.f, 
		[this](){return lights[1]->getIntensities().r < 0.2;},
			[this](){score+= 100;}, 
			[this](){score-= 100;});
	eventQueue.expectAt(135.0f + offset + startSceneDelay, 5.f, 
		[this](){return lights[3]->getIntensities().r < 0.2;},
			[this](){incScore();}, 
			[this](){decScore();});
	
#pragma endregion 

#pragma region ControllerSetup

	controller->lightSliderOne.bind([this](int _value){
		lights[1]->setIntensities(glm::vec3((static_cast<float>(_value) + 0.0001f)/1024));
	});

	controller->lightSliderTwo.bind([this](int _value){
		lights[2]->setIntensities(glm::vec3((static_cast<float>(_value) + 0.0001f)/1024));
	});

	controller->lightSliderThree.bind([this](int _value){
		lights[3]->setIntensities(glm::vec3((static_cast<float>(_value) + 0.0001f)/1024));
	});

	controller->setButtonOne.bind([this](int _value) {
		if(controller->setButtonOne.justDown()) {
			//setPeiceBuilding->lower();
		}
	});

	controller->setButtonTwo.bind([this](int _value) {
		if(controller->setButtonTwo.justDown()) {
			if( eventQueue.getRelativeTime() < (53.0 + startSceneDelay)){
				setPieceLuggage->toggle(4.5f);
			}
			if( eventQueue.getRelativeTime() > (53.0 + startSceneDelay)){
				lease->setVisible(true);
			}
		}
	});

	controller->setButtonThree.bind([this](int _value) {
		if(controller->setButtonThree.justDown()) {
			setPieceBed->toggle(4.5f);
			setPieceFireplace->toggle(4.5f);
		}
	});

	controller->setButtonFour.bind([this](int _value) {
		if(controller->setButtonFour.justDown()) {
			setPieceWeb->toggle(5.0f);
		}
	});
	
	// Move this into stage scene
	controller->specialCurtainPot.bind([this](int _value){
		if(!controller->connected){
			_value = 1024; 
		}
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

	controller->specialFireButton.bind([this](int _value) {
		if(controller->specialFireButton.justDown()) {
			fireActive = !fireActive;
		}
	});

	controller->soundMicSwitch.bind([this](int _value) {
		if(!controller->connected){
			_value = 1; 
		}
		if(_value == 1) {
			dialoguePlayer->unmute();
		}else {
			dialoguePlayer->mute(); 
		}
	});

	controller->soundButtonOne.bind([this](int _value) {
		if(controller->soundButtonOne.justDown()) {
			if( eventQueue.getRelativeTime() > (11.0 + startSceneDelay) && eventQueue.getRelativeTime() < (30.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("HowlingWolf1" )->sound->play();
				conditions["wolfCallPlayed"] = true;
			}
			if( eventQueue.getRelativeTime() > (73.0 + startSceneDelay) && eventQueue.getRelativeTime() < (77.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("doorKnock" )->sound->play();
				if(conditions["boxSound1Played"] == true){
					if(conditions["boxSound2Played"] == true){
						conditions["boxSound3Played"] = true;
					}else
						conditions["boxSound2Played"] = true;
				}else
					conditions["boxSound1Played"] = true;
			}
			if( eventQueue.getRelativeTime() > (87.0 + startSceneDelay) && eventQueue.getRelativeTime() < (100.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("PaperclipCut" )->sound->play();
				conditions["paperCutSoundPlayed"] = true;
			}
			if( eventQueue.getRelativeTime() > (120.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bat1" )->sound->play();
				conditions["batSoundPlayed"] = true;
			}
		}
	});

	controller->soundButtonTwo.bind([this](int _value) {
		if(controller->soundButtonTwo.justDown()) {
			if( eventQueue.getRelativeTime() > (0.0 + startSceneDelay) && eventQueue.getRelativeTime() < (4.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("DraculaSound" )->sound->play();
				conditions["draculaSoundPlayed"] = true;
			}
			if( eventQueue.getRelativeTime() > (90.0 + startSceneDelay) && eventQueue.getRelativeTime() < (110.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("pouringWine" )->sound->play();
				conditions["wineSoundPlayed"] = true;
			}
			if( eventQueue.getRelativeTime() > (110.0 + startSceneDelay)){
				if(conditions["doorSoundPlayed"] == true){
					TTFB_ResourceManager::scenario->getAudio("fall" )->sound->play();
					conditions["faintSoundPlayed"] = true;
				}
				else{
				TTFB_ResourceManager::scenario->getAudio("doorClosing" )->sound->play();
				conditions["doorSoundPlayed"] = true;
				}
			}
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

	if(fireTimer < 1.0 && fireActive && _step->time - lastFireEmission > 0.15f){
		Particle * p = fireSystem->addParticle(glm::vec3(16,  stage->getVisibleBounds().getBottomRight().y + 5.f, 0), TTFB_ResourceManager::scenario->getTexture("fireRed")->texture);
		Particle * p1 = fireSystem->addParticle(glm::vec3(16, stage->getVisibleBounds().getBottomRight().y + 5.f, 0), TTFB_ResourceManager::scenario->getTexture("fireOrange")->texture);
		Particle * p2 = fireSystem->addParticle(glm::vec3(16, stage->getVisibleBounds().getBottomRight().y + 5.f, 0), TTFB_ResourceManager::scenario->getTexture("fireYellow")->texture);
		Particle * p3 = fireSystem->addParticle(glm::vec3(16, stage->getVisibleBounds().getBottomRight().y + 5.f, 0), TTFB_ResourceManager::scenario->getTexture("smoke")->texture);
		lastFireEmission = _step->time;
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
		TTFB_StageScene::endScene(DRACULA, MENU, "draculaWin", "Ending");
	}
}
