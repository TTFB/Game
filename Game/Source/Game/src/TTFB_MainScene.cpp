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

TTFB_MainScene::TTFB_MainScene(Game * _game) :
	TTFB_StageScene(_game, 100.0f, "L1_Floor", "L1_Side", "L1_Background", "L1_Top", "L1_Bottom")
{

	SpotLight * light2 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.01f, 0.001f, -1.f);
	lights.push_back(light2);
	childTransform->addChild(light2);
	light2->firstParent()->translate(0, 0, 30);

	TTFB_Actor * kingArthur = createActor("kingArthur");
	childTransform->addChild(kingArthur);
	kingArthur->translateComponents(-10.f, kingArthur->getLegsOffset(), 0.f);

	TTFB_Actor * blackKnight = createActor("kingArthur");
	childTransform->addChild(blackKnight);
	blackKnight->translateComponents(10.f, blackKnight->getLegsOffset(), 0.f);

	blackKnight->flip();

	eventQueue.at(4.0f, [=](){
		blackKnight->say(2.0f, L"None shall pass", true);
	});

	eventQueue.at(6.5f, [=](){
		kingArthur->say(1.0f, L"What?", true);
	});

	eventQueue.at(8.0f, [=](){
		blackKnight->say(2.0f, L"None shall pass", true);
	});
	
	eventQueue.at(10.5, [=](){
		kingArthur->say(4.0f, L"I have no quarrel with you, good Sir knight", false);
	});
	
	eventQueue.at(14.5f, [=](){
		kingArthur->say(3.0f, L"but I must cross this bridge", true);
	});

	eventQueue.at(18.0f, [=](){
		blackKnight->say(2.0f, L"Then you shall die", true);
	});

	eventQueue.at(20.0f, [=](){
		kingArthur->say(3.0f, L"I command you as King of the Britons to stand aside!", true);
		kingArthur->move(7.0f);
	});

	eventQueue.at(23.0f, [=](){
		blackKnight->say(2.0f, L"I move for no man", true);
	});

	eventQueue.at(25.0f, [=](){
		kingArthur->say(3.0f, L"So be it!", true)->subscribe(
			[=](){
				blackKnight->breakLeftArmJoint();		
				blackKnight->applyImpulseLeftArm(0.0f, 5.0f);
			}
		);
	});

	eventQueue.at(29.0f, [=](){
		kingArthur->say(2.0f, L"Now stand aside, worthy adversary", true);
	});

	eventQueue.at(31.0f, [=](){
		blackKnight->say(2.0f, L"'Tis but a scratch", true);
	});

	eventQueue.at(33.0f, [=](){
		kingArthur->say(2.0f, L"A scratch? Your arm's off", true);
	});

	eventQueue.at(35.0f, [=](){
		blackKnight->say(2.0f, L"No it isn't", true);
	});

	eventQueue.at(37.0f, [=](){
		kingArthur->say(2.0f, L"What's that then?", true);
	});

	eventQueue.at(39.0f, [=](){
		blackKnight->say(2.0f, L"I've had worse", true);
	});

	eventQueue.at(41.0f, [=](){
		kingArthur->say(2.0f, L"You liar!", true);
	});

	eventQueue.at(43.0f, [=](){
		blackKnight->say(2.0f, L"Come on you pansy!", true);
	});

	eventQueue.at(45.0f, [=](){
		kingArthur->say(1.0f, L"Hah", true)->subscribe(
			[=](){
				blackKnight->breakRightArmJoint();
				blackKnight->applyImpulseRighttArm(0.0f, 5.0f);
			}
		);
	});

	eventQueue.at(47.0f, [=](){
		kingArthur->say(2.0f, L"Victory is mine!", true);
	});

	eventQueue.at(47.0f, [=](){
		kingArthur->say(2.0f, L"Victory is mine!", false);
	});

	eventQueue.at(49.0f, [=](){
		kingArthur->say(2.0f, L"We thank the Lord, that in thy merc-", true);
	});

	eventQueue.at(50.7f, [=](){
		blackKnight->say(2.0f, L"Come on then", true);
	});

	eventQueue.at(53.f, [=](){
		kingArthur->say(1.0f, L"What?", true);
	});

	eventQueue.at(54.f, [=](){
		blackKnight->say(1.5f, L"Have at you!", true);
	});

	eventQueue.at(55.5f, [=](){
		kingArthur->say(2.0f, L"You are indeed brave, Sir Knight?", false);
	});

	eventQueue.at(57.5f, [=](){
		kingArthur->say(1.5f, L"but this fight is mine", true);
	});

	eventQueue.at(59.f, [=](){
		blackKnight->say(2.0f, L"Oh, had enough, eh?", true);
	});

	eventQueue.at(61.f, [=](){
		kingArthur->say(2.0f, L"Look, you stupid bastard", false);
	});

	eventQueue.at(63.f, [=](){
		kingArthur->say(2.0f, L"you've got no arms left", true);
	});

	eventQueue.at(65.f, [=](){
		blackKnight->say(2.0f, L"Yes I have", true);
	});

	eventQueue.at(67.f, [=](){
		kingArthur->say(1.0f, L"Look!", true);
	});

	eventQueue.at(68.f, [=](){
		blackKnight->say(2.0f, L"Just a flesh wound", true);
	});
	
	eventQueue.at(70.f, [=](){
		kingArthur->say(2.0f, L"Look, stop that", true);
	});

	eventQueue.at(72.f, [=](){
		blackKnight->say(2.0f, L"Chicken! Chicken!", true);
	});

	eventQueue.at(74.f, [=](){
		kingArthur->say(2.0f, L"I'll have your legs. Right!", true)->subscribe(
			[=](){
				blackKnight->breakLegsJoint();
				blackKnight->applyImpulseLegs(0.3f, 5.0f);
				blackKnight->rootComponent->body->SetType(b2_dynamicBody);
			}
		);
	});

	eventQueue.at(78.f, [=](){
		blackKnight->say(2.0f, L"Right, I'll do you for that!", true);
	});

	eventQueue.at(80.f, [=](){
		kingArthur->say(2.0f, L"You'll what?", true);
	});

	eventQueue.at(82.f, [=](){
		blackKnight->say(2.0f, L"Come 'ere!", true);
	});

	eventQueue.at(84.f, [=](){
		kingArthur->say(2.0f, L"What are you going to do, bleed on me?", true);
	});

	eventQueue.at(86.f, [=](){
		blackKnight->say(2.0f, L"I'm invincible!", true);
	});

	eventQueue.at(88.f, [=](){
		kingArthur->say(2.0f, L"You're a loony", true);
	});

	eventQueue.at(90.f, [=](){
		blackKnight->say(2.0f, L"The Black Knight always triumphs!", true);
	});

	eventQueue.at(92.f, [=](){
		blackKnight->say(2.0f, L"Have at you! Come on then", true);
	});

	eventQueue.at(94.f, [=](){
		blackKnight->say(2.0f, L"All right; we'll call it a draw", true);
	});

	eventQueue.at(96.f, [=](){
		kingArthur->say(2.0f, L"Come, Patsy", true)->subscribe(
			[=](){
				kingArthur->move(15.0f);
			}
		);
	});
	
	eventQueue.at(98.f, [=](){
		blackKnight->say(2.0f, L"Oh, oh, I see, running away then", false);
	});
	
	eventQueue.at(100.f, [=](){
		blackKnight->say(2.0f, L"You yellow bastards!", false);
	});

	eventQueue.at(102.f, [=](){
		blackKnight->say(2.0f, L"Come back here and takes what's coming to you", false);
	});

	eventQueue.at(104.f, [=](){
		blackKnight->say(2.0f, L"I'll bite your legs off!", true);
	});

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
}

TTFB_MainScene::~TTFB_MainScene(){
}

void TTFB_MainScene::update(Step * _step){

	float lightOneVal = controller->soundButtonOne.currentState;
	lights[0]->setIntensities(glm::vec3(lightOneVal + 0.5f));

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