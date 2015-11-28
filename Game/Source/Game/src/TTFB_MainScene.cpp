#pragma once

#include <TTFB_MainScene.h>
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

TTFB_MainScene::TTFB_MainScene(Game * _game) :
	TTFB_StageScene(_game, 100.0f, "L1_Floor", "L1_Side", "L1_Background", "L1_Top", "L1_Bottom"),
	bgMusicStarted(false)
{

#pragma region LightSetup
	
	SpotLight * light0 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(0,0,0), 45.f, 0.001f, 0.001f, -1.f);
	lights.push_back(light0);
	childTransform->addChild(light0);
	light0->firstParent()->translate(0, 0, 30);
	
	SpotLight * light1 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.001f, 0.001f, -1.f);
	lights.push_back(light1);
	childTransform->addChild(light1);
	light1->firstParent()->translate(-20, 10, 13);

	SpotLight * light2 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.001f, 0.001f, -1.f);
	lights.push_back(light2);
	childTransform->addChild(light2);
	light2->firstParent()->translate(0, 10, 13);

	SpotLight * light3 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.001f, 0.001f, -1.f);
	lights.push_back(light3);
	childTransform->addChild(light3);
	light3->firstParent()->translate(20, 10, 13);

#pragma endregion 

#pragma region ActorSetup

	kingArthur = createActor("kingArthur");
	childTransform->addChild(kingArthur);
	kingArthur->translateComponents(-10.f, kingArthur->getLegsOffset(), 0.f);

	blackKnight = createActor("blackKnight");
	childTransform->addChild(blackKnight);
	blackKnight->translateComponents(10.f, blackKnight->getLegsOffset(), 0.f);

	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);
	
	blackKnight->flip();

	kingArthur->pickupPropRight(addProp("sword", glm::vec3(-8, 10, 0.f)));

#pragma endregion 

#pragma region SetSetup

	setPiece = addSetPiece("L1_Tree2", glm::vec3(0.f, 20.f, -0.5f));
	setPiece->raise();

#pragma endregion 

#pragma region ControllerBindings
	
	// Setup Controller Bindings
	controller->lightSliderOne.bind([=](int _value){
		lights[1]->setIntensities(glm::vec3(((float)_value + 0.0001f)/256));
	});

	controller->lightSliderTwo.bind([=](int _value){
		lights[2]->setIntensities(glm::vec3(((float)_value + 0.0001f)/256));
	});

	controller->lightSliderThree.bind([=](int _value){
		lights[3]->setIntensities(glm::vec3(((float)_value + 0.0001f)/256));
	});
	
	// Move this into stage scene
	controller->specialCurtainPot.bind([=](int _value){
		float increase = _value / 30.0f;
		glm::vec3 leftTrans = stage->curtainLeft->firstParent()->getTranslationVector();
		glm::vec3 rightTrans = stage->curtainRight->firstParent()->getTranslationVector();
		leftTrans.x  = (-increase - 12);
		rightTrans.x = (increase + 12);
		stage->curtainLeft->firstParent()->translate(leftTrans, false);
		stage->curtainRight->firstParent()->translate(rightTrans, false);
	});

	controller->setButtonOne.bind([=](int _value) {
		if(controller->setButtonOne.justDown()) {
			setPiece->toggle();
		}
	});

	controller->setButtonTwo.bind([=](int _value) {
		if(controller->setButtonTwo.justDown()) {
			// Toggle second set piece
		}
	});

	controller->setButtonThree.bind([=](int _value) {
		if(controller->setButtonThree.justDown()) {
			// Toggle third set piece
		}
	});

	controller->setButtonFour.bind([=](int _value) {
		if(controller->setButtonFour.justDown()) {
			// Toggle fourth set piece
		}
	});

	controller->soundButtonOne.bind([=](int _value) {
		if(controller->soundButtonOne.justDown()) {
			// Play sound effect
		}
	});

	controller->soundButtonTwo.bind([=](int _value) {
		if(controller->soundButtonTwo.justDown()) {
			// Play sound effect
		}
	});

	controller->soundButtonThree.bind([=](int _value) {
		if(controller->soundButtonThree.justDown()) {
			// Play sound effect
		}
	});

	controller->specialFireButton.bind([=](int _value) {
		if(controller->specialFireButton.justDown()) {
			fireActive = !fireActive;
		}
	});

	controller->specialFogSwitch.bind([=](int _value) {
		if(controller->specialFireButton.justDown()) {
			// Toggle fog
		}
	});

	controller->soundMicSwitch.bind([=](int _value) {
		if(_value == 1) {
			dialoguePlayer->unmute();
		}else {
			dialoguePlayer->mute();
		}
	});
	
#pragma endregion 

#pragma region AudioSetup

	backgroundMusic = TTFB_ResourceManager::scenario->getAudio("spamalot_bg")->sound;
	dialoguePlayer = new TTFB_DialoguePlayer("spamalot");

#pragma endregion 

#pragma region Events

	eventQueue.at(4.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"None shall pass", true);
	});

	eventQueue.at(6.5f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(1.5f, L"What?", true);
	});

	eventQueue.at(8.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"None shall pass", true);
		kingArthur->swingRightArm();
	});
	
	eventQueue.at(10.5, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(4.0f, L"I have no quarrel with you, good Sir knight", false);
	});
	
	eventQueue.at(14.5f, [=](){
		kingArthur->say(3.0f, L"but I must cross this bridge", true);
	});

	eventQueue.at(18.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Then you shall die", true);
	});

	eventQueue.at(20.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(3.0f, L"I command you as King of the Britons to stand aside!", true);
		kingArthur->move(7.0f);
	});

	eventQueue.at(23.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I move for no man", true);
	});

	eventQueue.at(25.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(3.0f, L"So be it!", true)->subscribe(
			[=](){
				blackKnight->breakLeftArmJoint();		
				blackKnight->applyImpulseLeftArm(0.0f, 5.0f);
			}
		);
	});

	eventQueue.at(29.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Now stand aside, worthy adversary", true);
	});

	eventQueue.at(31.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"'Tis but a scratch", true);
	});

	eventQueue.at(33.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"A scratch? Your arm's off", true);
	});

	eventQueue.at(35.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"No it isn't", true);
	});

	eventQueue.at(37.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"What's that then?", true);
	});

	eventQueue.at(39.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I've had worse", true);
	});

	eventQueue.at(41.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You liar!", true);
	});

	eventQueue.at(43.0f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come on you pansy!", true);
	});

	eventQueue.at(45.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Hah", true)->subscribe(
			[=](){
				blackKnight->breakRightArmJoint();
				blackKnight->applyImpulseRighttArm(0.0f, 5.0f);
			}
		);
	});

	eventQueue.at(47.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Victory is mine!", true);
	});

	eventQueue.at(49.0f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"We thank the Lord, that in thy merc-", true);
	});

	eventQueue.at(50.7f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come on then", true);
	});

	eventQueue.at(53.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"What?", true);
	});

	eventQueue.at(54.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(1.5f, L"Have at you!", true);
	});

	eventQueue.at(55.5f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You are indeed brave, Sir Knight?", false);
	});

	eventQueue.at(57.5f, [=](){
		kingArthur->say(1.5f, L"but this fight is mine", true);
	});

	eventQueue.at(59.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Oh, had enough, eh?", true);
	});

	eventQueue.at(61.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Look, you stupid bastard", false);
	});

	eventQueue.at(63.f, [=](){
		kingArthur->say(2.0f, L"you've got no arms left", true);
	});

	eventQueue.at(65.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Yes I have", true);
	});

	eventQueue.at(67.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(1.0f, L"Look!", true);
	});

	eventQueue.at(68.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Just a flesh wound", true);
	});
	
	eventQueue.at(70.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Look, stop that", true);
	});

	eventQueue.at(72.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Chicken! Chicken!", true);
	});

	eventQueue.at(74.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"I'll have your legs. Right!", true)->subscribe(
			[=](){
				blackKnight->breakLeftLegJoint();
				blackKnight->applyImpulseLegs(0.3f, 5.0f);
				blackKnight->rootComponent->body->SetType(b2_dynamicBody);
			}
		);
	});

	eventQueue.at(78.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Right, I'll do you for that!", true);
	});

	eventQueue.at(80.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You'll what?", true);
	});

	eventQueue.at(82.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come 'ere!", true);
	});

	eventQueue.at(84.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"What are you going to do, bleed on me?", true);
	});

	eventQueue.at(86.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I'm invincible!", true);
	});

	eventQueue.at(88.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"You're a loony", true);
	});

	eventQueue.at(90.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"The Black Knight always triumphs!", true);
	});

	eventQueue.at(92.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Have at you! Come on then", true);
	});

	eventQueue.at(94.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"All right; we'll call it a draw", true);
	});

	eventQueue.at(96.f, [=](){
		dialoguePlayer->playNext();
		kingArthur->say(2.0f, L"Come, Patsy", true)->subscribe(
			[=](){
				kingArthur->move(15.0f);
			}
		);
	});
	
	eventQueue.at(98.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Oh, oh, I see, running away then", false);
	});
	
	eventQueue.at(100.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"You yellow bastards!", false);
	});

	eventQueue.at(102.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"Come back here and takes what's coming to you", false);
	});

	eventQueue.at(104.f, [=](){
		dialoguePlayer->playNext();
		blackKnight->say(2.0f, L"I'll bite your legs off!", true);
	});

#pragma endregion 

	//eventQueue.at(6.0f, [=](){
	//	kingArthur->say(1.0f, L"What?", true);
	//});

	/*int * i = new int(0);

	eventQueue.at(6.f, [=](){
			//ent->setCurrentAnimation("walk");
			kingArthur->move(3.0f)->subscribe([=](){
				//ent->setCurrentAnimation("stand");
			});
		});
	eventQueue.expectAt(6.f, 2.f, 
		[i](){return *i == 1;},
		[](){std::cout<<"Success";}, 
		[](){std::cout<<"Failure";});
	eventQueue.at(7.f,  [i](){*i = 1;});
	eventQueue.at(7.f,  [i](){*i = 1;});
	eventQueue.at(9.f,  [=](){kingArthur->say(2.0f, L"fsdf",  true)->subscribe(
			[=](){kingArthur->say(2.0f, L"sasas", true);}
		);
	});
	eventQueue.at(11.f, [=](){
		//ent->setCurrentAnimation("walk");
		kingArthur->flip();
		kingArthur->move(-7.0f)->subscribe([=](){
			//ent->setCurrentAnimation("stand");
		});
	}); 

	eventQueue.when([=](){
			return *i == 1;
		},
		[=](){
			kingArthur->say(3.0f, L"wwoowowowo", false);
		}
	);*/

	addFog();
}

TTFB_MainScene::~TTFB_MainScene(){
}

void TTFB_MainScene::update(Step * _step){

	//float lightOneVal = controller->soundButtonOne.currentState;
	//lights[0]->setIntensities(glm::vec3(lightOneVal + 0.5f));

	if(!bgMusicStarted) {
		bgMusicStarted = true;
		backgroundMusic->play();
	}

	fireActive = true;
	
	if(fireActive){
		b2Vec2 blackKnightPos = blackKnight->getBox2dPos();
		Particle * p = fireSystem->addParticle(glm::vec3(blackKnightPos.x + 3, stage->getVisibleBounds().getBottomRight().y + 0.2f, 0), TTFB_ResourceManager::scenario->getTexture("blood")->texture);
	}

	eventQueue.update(_step);
	TTFB_StageScene::update(_step);
}

void TTFB_MainScene::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	TTFB_StageScene::render(_matrixStack, _renderOptions);
}

void TTFB_MainScene::load(){
	TTFB_StageScene::load();
}

void TTFB_MainScene::unload(){
	TTFB_StageScene::unload();	
}