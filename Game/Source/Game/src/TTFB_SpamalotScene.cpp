#pragma once

#include <TTFB_SpamalotScene.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Stage.h>
#include <TTFB_StageScene.h>
#include <TTFB_Controller.h>

#include <Game.h>
#include <MeshEntity.h>
#include <MeshInterface.h>
#include <MeshFactory.h>
#include <Resource.h>

#include <DirectionalLight.h>
#include <PointLight.h>
#include <SpotLight.h>

#include <shader\ComponentShaderBase.h>
#include <shader\ComponentShaderText.h>
#include <shader\ShaderComponentText.h>
#include <shader\ShaderComponentTexture.h>
#include <shader\ShaderComponentDiffuse.h>
#include <shader\ShaderComponentHsv.h>
#include <shader\ShaderComponentMVP.h>

#include <shader\ShaderComponentIndexedTexture.h>
#include <TextureColourTable.h>

#include <Box2DWorld.h>
#include <Box2DMeshEntity.h>
#include <Box2DDebugDrawer.h>

#include <MousePerspectiveCamera.h>
#include <FollowCamera.h>

#include <System.h>
#include <Mouse.h>
#include <Keyboard.h>
#include <GLFW\glfw3.h>

#include <RenderSurface.h>
#include <StandardFrameBuffer.h>
#include <NumberUtils.h>

#include <NodeBulletBody.h>
#include <BulletMeshEntity.h>
#include <TextArea.h>
#include <SpriteSheetAnimation.h>
#include <Box2DSprite.h>
#include <TTFB_Constants.h>
#include <VerticalLinearLayout.h>
#include <TTFB_SetPiece.h>
#include <ParticleSystem.h>
#include <TTFB_Audience.h>

TTFB_SpamalotScene::TTFB_SpamalotScene(Game * _game) :
	TTFB_StageScene(_game, 100.0f, "L1_Floor", "L1_Side", "L1_Background", "L1_Top", "L1_Bottom"),
	bgMusicStarted(false),
	lastFireEmission(0.0)
{
	conditions["blood1Played"] = false; //holds like a bool
	conditions["blood2Played"] = false; 
	conditions["blood3Played"] = false; 
	conditions["blood4Played"] = false; 
	conditions["whoosh1Played"] = false; 
	conditions["chickenPlayed"] = false; 


#pragma region SetSetup

	setPieceTree1 = addSetPiece("L1_Tree1", glm::vec3(10.f, 20.f, -0.5f));
	setPieceTree1->raise();
	setPieceTree2 = addSetPiece("L1_Tree2", glm::vec3(-10.f, 20.f, -0.5f));
	setPieceTree2->raise();
	setPieceBush = addSetPiece("L1_Bush", glm::vec3(0.f, 20.f, -0.5f));
	setPieceBush->raise();
	setPieceMatte = addSetPiece("L1_mattePainting", glm::vec3(0.f, 60.f, -2.0f));
	setPieceMatte->raise();

#pragma endregion 
	
#pragma region ActorSetup

	kingArthur = createActor("kingArthur");
	childTransform->addChild(kingArthur);
	kingArthur->translateComponents(-20.f, kingArthur->getLegsOffset(), 0.f);

	blackKnight = createActor("blackKnight");
	childTransform->addChild(blackKnight);
	blackKnight->translateComponents(8.0f, blackKnight->getLegsOffset(), 0.f);

	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);
	
	blackKnight->flip();

	kingArthur->pickupPropRight(addProp("sword", glm::vec3(-8, 10, 0.f)));

#pragma endregion 

#pragma region ControllerBindings
	
	// Setup Controller Bindings
	controller->lightSliderOne.bind([this](int _value){
		lights[1]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
	});

	controller->lightSliderTwo.bind([this](int _value){
		lights[2]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
	});

	controller->lightSliderThree.bind([this](int _value){
		lights[3]->setIntensities(glm::vec3(((float)_value + 0.0001f)/1024));
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

	controller->setButtonOne.bind([this](int _value) {
		if(controller->setButtonOne.justDown()) {
			setPieceTree1->toggle();
			setPieceTree2->toggle();
			setPieceBush->toggle();	
		}
	});

	controller->setButtonTwo.bind([this](int _value) {
		if(controller->setButtonTwo.justDown()) {
			setPieceMatte->toggle();
		}
	});

	controller->setButtonThree.bind([this](int _value) {
		if(controller->setButtonThree.justDown()) {
			
		}
	});

	controller->setButtonFour.bind([this](int _value) {
		if(controller->setButtonFour.justDown()) {
			std::cout<<"Yellow SET";
			std::cout<<eventQueue.getRelativeTime();
			if( eventQueue.getRelativeTime() > (16.0 + startSceneDelay) && eventQueue.getRelativeTime() < (25.0 + startSceneDelay)){
				std::cout<<"IN TRIGGER ARMLEFT";
				blackKnight->breakLeftArmJoint();
				blackKnight->applyImpulseLeftArm(0.0f, 5.0f);
			}
			if( eventQueue.getRelativeTime() > (34.5 + startSceneDelay) && eventQueue.getRelativeTime() < (38.5 + startSceneDelay)){
				std::cout<<"IN TRIGGER ARMRIGHT";
				blackKnight->breakRightArmJoint();
				blackKnight->applyImpulseRighttArm(0.0f, 5.0f);
			}
			if( eventQueue.getRelativeTime() > (63.0 + startSceneDelay) && eventQueue.getRelativeTime() < (71.0 + startSceneDelay)){
				std::cout<<"IN TRIGGER LEFTLEG";
				blackKnight->breakLeftLegJoint();
				blackKnight->applyImpulseLegs(0.3f, 5.0f);
				blackKnight->rootComponent->body->SetType(b2_dynamicBody);
			}
			if( eventQueue.getRelativeTime() > (81.0 + startSceneDelay) && eventQueue.getRelativeTime() < (85.0 + startSceneDelay)){
				std::cout<<"IN TRIGGER LEFTRIGHT";
				blackKnight->breakRightLegJoint();
				blackKnight->applyImpulseLegs(0.3f, 5.0f);
				blackKnight->rootComponent->body->SetType(b2_dynamicBody);
			}
		}
	});

	controller->soundButtonOne.bind([this](int _value) {
		if(controller->soundButtonOne.justDown()) {
			if( eventQueue.getRelativeTime() > (15.0 + startSceneDelay) && eventQueue.getRelativeTime() < (19.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bloodSpurt3" )->sound->play();
				conditions["blood1Played"] = true;
			}
			else if( eventQueue.getRelativeTime() > (34.5 + startSceneDelay) && eventQueue.getRelativeTime() < (38.5 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bloodSpurt1" )->sound->play();
				conditions["blood2Played"] = true;
			}
			else if( eventQueue.getRelativeTime() > (63.0 + startSceneDelay) && eventQueue.getRelativeTime() < (67.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bloodSpurt3" )->sound->play();
				conditions["blood3Played"] = true;
			}
			else if( eventQueue.getRelativeTime() > (81.0 + startSceneDelay) && eventQueue.getRelativeTime() < (85.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bloodSpurt1" )->sound->play();
				conditions["blood4Played"] = true;
			}
			
		}
	});

	controller->soundButtonTwo.bind([this](int _value) {
		if(controller->soundButtonTwo.justDown()) {
			if( eventQueue.getRelativeTime() > (57.0 + startSceneDelay) && eventQueue.getRelativeTime() < (61.0 + startSceneDelay)){
				TTFB_ResourceManager::scenario->getAudio("bloodSpurt3" )->sound->play();
				conditions["swordMiss"] = true;
			}
			
		}
	});
	
	controller->soundButtonThree.bind([this](int _value) {
		if(controller->soundButtonThree.justDown()) {
			TTFB_ResourceManager::scenario->getAudio("chicken1" )->sound->play();
		}
	});

	controller->specialFireButton.bind([this](int _value) {
		if(controller->specialFireButton.justDown()) {
			fireActive = !fireActive;
		}
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
	startSceneDelay = 10.0f;
	//scene setup cues
	eventQueue.expectAt(5.f, 5.f, 
		[this](){return !dialoguePlayer->muted;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(5.f, 5.f, 
		[this](){return setPieceTree1->isLowered();},
		[this](){incScore();}, 
		[this](){decScore();});
	eventQueue.expectAt(5.f, 5.f,
		[this](){return setPieceMatte->isLowered();},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(5.f, 5.f, 
		[this](){return lights[1]->getIntensities().r > 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(5.f, 5.f, 
		[this](){return lights[2]->getIntensities().r > 3.5;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(5.f, 5.f, 
		[this](){return stage->curtainLeft->firstParent()->getTranslationVector().x < -44.0f;},
			[this](){incScore();}, 
			[this](){decScore();});

	//light 0%
	eventQueue.expectAt(1.5f + startSceneDelay, 4.f, 
		[this](){return lights[1]->getIntensities().r < 0.2;},
			[this](){incScore();}, 
			[this](){decScore();});
	//fog ON
	eventQueue.expectAt(11.5f + startSceneDelay, 4.f, 
		[this](){return fogActive == true;},
			[this](){incScore();}, 
			[this](){decScore();});
	//fog OFF
	eventQueue.expectAt(15.0f + startSceneDelay, 4.f, 
		[this](){return fogActive == false;},
			[this](){incScore();}, 
			[this](){decScore();});
	//sound2 effect
	eventQueue.expectAt(17.0f + startSceneDelay, 4.f, 
		[this](){return conditions["blood1Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//set3 - arm off
	eventQueue.expectAt(21.0f + startSceneDelay, 4.f, 
		[this](){return blackKnight->rightArmBroken;},
			[this](){incScore();}, 
			[this](){decScore();});
	//sound2 effect
	eventQueue.expectAt(36.5f + startSceneDelay, 4.f, 
		[this](){return conditions["blood2Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//set3 - arm off
	eventQueue.expectAt(36.5f + startSceneDelay, 4.f, 
		[this](){return blackKnight->leftArmBroken;},
			[this](){incScore();}, 
			[this](){decScore();});
	//fire
	eventQueue.expectAt(42.5f + startSceneDelay, 4.f,
		[this](){return fireActive;},
			[this](){incScore();}, 
			[this](){decScore();});
	//lights(1&3) 50%
	eventQueue.expectAt(51.f + startSceneDelay, 6.0f, 
		[this](){return lights[1]->getIntensities().r > 1 && lights[1]->getIntensities().r < 3;},
			[this](){std::cout<<"SuccessL1";}, 
			[this](){std::cout<<"FailureL1";});
	eventQueue.expectAt(51.f + startSceneDelay, 6.0f, 
		[this](){return lights[3]->getIntensities().r > 1 && lights[3]->getIntensities().r < 3;},
			[this](){std::cout<<"SuccessL3";}, 
			[this](){std::cout<<"FailureL3";});
	//sound - whoosh
	eventQueue.expectAt(59.f + startSceneDelay, 4.f, 
		[this](){return conditions["whoosh1Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//fire
	eventQueue.expectAt(59.f + startSceneDelay, 4.f,
		[this](){return fireActive;},
			[this](){incScore();}, 
			[this](){decScore();});
	//sound3 - chicken
	eventQueue.expectAt(63.f + startSceneDelay, 4.f, 
		[this](){return conditions["chickenPlayed"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//sound2 - blood
	eventQueue.expectAt(65.0f + startSceneDelay, 4.f, 
		[this](){return conditions["blood3Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//set3 - leg off
	eventQueue.expectAt(67.0f + startSceneDelay, 4.f, 
		[this](){return blackKnight->leftLegBroken;},
			[this](){incScore();}, 
			[this](){decScore();});
	//lights(1&3) 100%
	eventQueue.expectAt(76.f + startSceneDelay, 6.0f, 
		[this](){return lights[1]->getIntensities().r > 3.5;},
			[this](){std::cout<<"SuccessL1";}, 
			[this](){std::cout<<"FailureL1";});
	eventQueue.expectAt(76.f + startSceneDelay, 6.0f, 
		[this](){return lights[3]->getIntensities().r > 3.5;},
			[this](){std::cout<<"SuccessL3";}, 
			[this](){std::cout<<"FailureL3";});
	//sound2 - blood
	eventQueue.expectAt(83.0f + startSceneDelay, 4.f, 
		[this](){return conditions["blood4Played"];},
			[this](){incScore();}, 
			[this](){decScore();});
	//set3 - leg off
	eventQueue.expectAt(83.0f + startSceneDelay, 4.f, 
		[this](){return blackKnight->rightLegBroken;},
			[this](){incScore();}, 
			[this](){decScore();});
	//////end scene
	eventQueue.expectAt(101.f + startSceneDelay, 5.f, 
		[this](){return dialoguePlayer->muted;},
			[this](){incScore();}, 
			[this](){decScore();});
	eventQueue.expectAt(101.f + startSceneDelay, 5.f, 
		[this](){return lights[1]->getIntensities().r < 0.2;},
			[this](){score+= 100;}, 
			[this](){score-= 100;});
	eventQueue.expectAt(101.f + startSceneDelay, 5.f, 
		[this](){return lights[2]->getIntensities().r < 0.2;},
			[this](){score+= 100;}, 
			[this](){score-= 100;});
	eventQueue.expectAt(101.f + startSceneDelay, 5.f, 
		[this](){return lights[3]->getIntensities().r < 0.2;},
			[this](){incScore();}, 
			[this](){decScore();;});
	eventQueue.expectAt(101.f + startSceneDelay, 5.f, 
		[this](){return stage->curtainLeft->firstParent()->getTranslationVector().x < -5.0f;},
			[this](){incScore();}, 
			[this](){decScore();});

#pragma region AudioSetup

	backgroundMusic = TTFB_ResourceManager::scenario->getAudio("spamalot_bg")->sound;
	backgroundMusic->setGain(0.5f);
	dialoguePlayer = new TTFB_DialoguePlayer("spamalot");
	 
#pragma endregion 

#pragma region Events

	eventQueue.at(startSceneDelay - 5.0f, [this](){dimHouseLights();});

	eventQueue.at(0.0f + startSceneDelay, [this](){
		kingArthur->speedMod = 1.0f;
		kingArthur->move(-7.0f);
	});

	eventQueue.at(1.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"None shall pass", true);
	});

	eventQueue.at(3.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.5f, L"What?", true);
	});

	eventQueue.at(5.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"None shall pass", true);
		kingArthur->swingRightArm();
	});
	
	eventQueue.at(7.5 + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"I have no quarrel with you, good Sir knight", false);
	});
	
	eventQueue.at(9.5f + startSceneDelay, [this](){
		kingArthur->say(2.0f, L"but I must cross this bridge", true);
	});

	eventQueue.at(11.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Then you shall die", true);
	});

	eventQueue.at(12.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.5f, L"I command you as King of the Britons to stand aside!", true);
		kingArthur->speedMod = 2.0f;
		kingArthur->move(0.0f);
	});

	eventQueue.at(15.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I move for no man", true);
	});

	eventQueue.at(17.0f + startSceneDelay, [this](){
		kingArthur->speedMod = 4.0f;
		kingArthur->move(7.0f);
	});

	eventQueue.at(17.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"So be it!", true);
	});

	/*eventQueue.at(17.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"So be it!", true)->subscribe(
			[this](){
				blackKnight->breakLeftArmJoint();		
				blackKnight->applyImpulseLeftArm(0.0f, 5.0f);
			}
		);
	});*/

	eventQueue.at(19.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Hah", true);
	});

	eventQueue.at(20.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.0f, L"Oii", true);
	});

	eventQueue.at(21.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(3.0f, L"Now stand aside, worthy adversary", true);
		kingArthur->move(-1.5f);
	});

	eventQueue.at(24.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"'Tis but a scratch", true);
	});

	eventQueue.at(26.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"A scratch? Your arm's off", true);
	});

	eventQueue.at(28.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"No it isn't", true);
	});

	eventQueue.at(30.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"What's that then?", true);
	});

	eventQueue.at(32.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.0f, L"I've had worse", true);
	});

	eventQueue.at(33.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.5f, L"You liar!", true);
	});

	eventQueue.at(34.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come on you pansy!", true);
	});

	eventQueue.at(36.5f + startSceneDelay, [this](){
		kingArthur->speedMod = 4.0f;
		kingArthur->move(5.0f);
	});

	eventQueue.at(36.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Hah", true);
	});

	eventQueue.at(37.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.0f, L"Oii", true);
	});

	eventQueue.at(38.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Victory is mine!", true);
	});

	eventQueue.at(40.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"We thank the Lord, that in thy merc-", true);
	});

	eventQueue.at(42.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.0f, L"Hah!", true);
		blackKnight->speedMod = 2.0f;
		blackKnight->move(6.0f);
	});

	eventQueue.at(43.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.0f, L"Come on then", true);
		blackKnight->speedMod = 1.0f;
		blackKnight->move(8.0f);
	});

	eventQueue.at(44.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"What?", true);
	});

	eventQueue.at(45.5f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(1.5f, L"Have at you!", true);
	});

	eventQueue.at(47.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You are indeed brave, Sir Knight?", false);
	});

	eventQueue.at(49.0f + startSceneDelay, [this](){
		kingArthur->say(1.5f, L"but this fight is mine", true);
		kingArthur->move(2.0f);
	});

	eventQueue.at(51.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Oh, had enough, eh?", true);
	});

	eventQueue.at(53.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Look, you stupid bastard", false);
	});

	eventQueue.at(55.0f + startSceneDelay, [this](){
		kingArthur->say(2.0f, L"you've got no arms left", true);
	});

	eventQueue.at(56.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Yes I have", true);
	});

	eventQueue.at(58.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Look!", true);
	});

	eventQueue.at(59.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Just a flesh wound", true);
	});
	
	eventQueue.at(61.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Look, stop that", true);
	});

	eventQueue.at(63.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Chicken! Chicken!", true);
	});

	eventQueue.at(65.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"I'll have your legs. Right!", true);
	});

	eventQueue.at(67.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Whop", true);
	});

	eventQueue.at(68.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Right, I'll do you for that!", true);
	});

	eventQueue.at(70.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You'll what?", true);
	});

	eventQueue.at(72.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come 'ere!", true);
	});

	eventQueue.at(74.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"What are you going to do, bleed on me?", true);
	});

	eventQueue.at(76.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I'm invincible!", true);
	});

	eventQueue.at(78.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You're a loony", true);
	});

	eventQueue.at(80.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"The Black Knight always triumphs!", true);
	});

	eventQueue.at(82.0f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Have at you! Come on then", true);
	});

	eventQueue.at(84.f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"All right; we'll call it a draw", true);
	});

	eventQueue.at(86.f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Come, Pansy", true)->subscribe(
			[this](){
				kingArthur->move(15.0f);
			}
		);
	});
	
	eventQueue.at(88.f + startSceneDelay, [this](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Oh, oh, I see, running away then", false);
	});
	
	eventQueue.at(90.f + startSceneDelay, [this](){
		blackKnight->say(2.0f, L"You yellow bastards!", false);
	});

	eventQueue.at(92.f + startSceneDelay, [this](){
		blackKnight->say(2.0f, L"Come back here and takes what's coming to you", false);
	});

	eventQueue.at(94.f + startSceneDelay, [this](){
		blackKnight->say(2.0f, L"I'll bite your legs off!", true);
	});

	eventQueue.at(110.f + startSceneDelay, [this](){
		endScene(SPAMALOT);
		OpenAL_Sound * sound =  TTFB_ResourceManager::scenario->getAudio("clapping1")->sound;
		sound->setGain(0.8f);
		sound->play();
	});

#pragma endregion 

	//eventQueue.at(6.0f, [this](){
	//	kingArthur->say(1.0f, L"What?", true);
	//});

	/*int * i = new int(0);

	eventQueue.at(6.f, [this](){
			//ent->setCurrentAnimation("walk");
			kingArthur->move(3.0f)->subscribe([this](){
				//ent->setCurrentAnimation("stand");
			});
		});
	eventQueue.expectAt(6.f, 2.f, 
		[i](){return *i == 1;},
		[](){std::cout<<"Success";}, 
		[](){std::cout<<"Failure";});
	eventQueue.at(7.f,  [i](){*i = 1;});
	eventQueue.at(7.f,  [i](){*i = 1;});
	eventQueue.at(9.f,  [this](){kingArthur->say(2.0f, L"fsdf",  true)->subscribe(
			[this](){kingArthur->say(2.0f, L"sasas", true);}
		);
	});
	eventQueue.at(11.f, [this](){
		//ent->setCurrentAnimation("walk");
		kingArthur->flip();
		kingArthur->move(-7.0f)->subscribe([this](){
			//ent->setCurrentAnimation("stand");
		});
	}); 

	eventQueue.when([this](){
			return *i == 1;
		},
		[this](){
			kingArthur->say(3.0f, L"wwoowowowo", false);
		}
	);*/

	addFog();

}

TTFB_SpamalotScene::~TTFB_SpamalotScene(){
}

void TTFB_SpamalotScene::update(Step * _step){

	//float lightOneVal = controller->soundButtonOne.currentState;
	//lights[0]->setIntensities(glm::vec3(lightOneVal + 0.5f));

	if(!bgMusicStarted) {
		bgMusicStarted = true;
		backgroundMusic->play();
	}

	//fireActive = true;
	
	if(fireTimer < 1.0 && fireActive && _step->time - lastFireEmission > 0.1f){
		b2Vec2 blackKnightPos = blackKnight->getBox2dPos();
		Particle * p = fireSystem->addParticle(glm::vec3(blackKnightPos.x + 3,  stage->getVisibleBounds().getBottomRight().y + 0.2f, 0),  TTFB_ResourceManager::scenario->getTexture("fireRed")->texture);
		Particle * p1 = fireSystem->addParticle(glm::vec3(blackKnightPos.x + 3, stage->getVisibleBounds().getBottomRight().y + 0.2f, 0), TTFB_ResourceManager::scenario->getTexture("fireOrange")->texture);
		Particle * p2 = fireSystem->addParticle(glm::vec3(blackKnightPos.x + 3, stage->getVisibleBounds().getBottomRight().y + 0.2f, 0), TTFB_ResourceManager::scenario->getTexture("fireYellow")->texture);
		Particle * p3 = fireSystem->addParticle(glm::vec3(blackKnightPos.x + 3, stage->getVisibleBounds().getBottomRight().y + 0.2f, 0), TTFB_ResourceManager::scenario->getTexture("smoke")->texture);
		lastFireEmission = _step->time;
	}

	eventQueue.update(_step);
	TTFB_StageScene::update(_step);
}

void TTFB_SpamalotScene::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	TTFB_StageScene::render(_matrixStack, _renderOptions);
}

void TTFB_SpamalotScene::load(){
	TTFB_StageScene::load();
}

void TTFB_SpamalotScene::leftArmBleed() {
	ParticleSystem * bloodSystem = new ParticleSystem(TTFB_ResourceManager::scenario->getTexture("blood")->texture, box2dWorld, 0);
	bloodSystem->setShader(baseShader, true);
	bloodSystem->emissionAmount = 5;
	bloodSystem->emissionRate   = 0.1f;
	bloodSystem->emissionTimer  = 0.1f;

	blackKnight->leftArmJointTransform->addChild(bloodSystem);
}

void TTFB_SpamalotScene::rightArmBleed() {
	ParticleSystem * bloodSystem = new ParticleSystem(TTFB_ResourceManager::scenario->getTexture("blood")->texture, box2dWorld, 0);
	bloodSystem->setShader(baseShader, true);
	bloodSystem->emissionAmount = 5;
	bloodSystem->emissionRate   = 0.1f;
	bloodSystem->emissionTimer  = 0.1f;
	
	blackKnight->rightArmJointTransform->addChild(bloodSystem);
}

void TTFB_SpamalotScene::leftLegBleed() {
	ParticleSystem * bloodSystem = new ParticleSystem(TTFB_ResourceManager::scenario->getTexture("blood")->texture, box2dWorld, 0);
	bloodSystem->setShader(baseShader, true);
	bloodSystem->emissionAmount = 5;
	bloodSystem->emissionRate   = 0.1f;
	bloodSystem->emissionTimer  = 0.1f;
	
	blackKnight->leftLegJointTransform->addChild(bloodSystem);
}

void TTFB_SpamalotScene::rightLegBleed() {
	ParticleSystem * bloodSystem = new ParticleSystem(TTFB_ResourceManager::scenario->getTexture("blood")->texture, box2dWorld, 0);
	bloodSystem->setShader(baseShader, true);
	bloodSystem->emissionAmount = 5;
	bloodSystem->emissionRate   = 0.1f;
	bloodSystem->emissionTimer  = 0.1f;
	
	blackKnight->rightLegJointTransform->addChild(bloodSystem);
}

void TTFB_SpamalotScene::unload(){
	TTFB_StageScene::unload();	
}