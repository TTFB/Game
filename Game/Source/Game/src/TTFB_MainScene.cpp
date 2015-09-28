#pragma once

#include <TTFB_MainScene.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Stage.h>
#include <TTFB_StageScene.h>

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

TTFB_MainScene::TTFB_MainScene(Game * _game) :
	TTFB_StageScene(_game, 50.0f)
{
	SpotLight * light2 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.01f, 0.001f, -1.f);
	lights.push_back(light2);
	debugCam->childTransform->addChild(light2);

	TTFB_Actor * ent = createActor();
	childTransform->addChild(ent);
	ent->setTranslationPhysical(0.f, 5.0f, 0.f);

	int * i = new int(0);

	eventQueue.at(6.f, [=]()
		{
			ent->move(3.0f);
		});
	eventQueue.expectAt(6.f, 2.f, 
		[i](){
			return *i == 1;
		},
		[](){
			std::cout<<"Success";
		}, 
		[](){
			std::cout<<"Failure";
		});
	eventQueue.at(7.f,  [i](){
			*i = 1;
		});
	eventQueue.at(9.f, [=](){
		ent->say(2.0f, L"fsdf",  false);
	});
	eventQueue.at(11.f, [=](){
		ent->say(2.0f, L"sasas", true);
	});
	eventQueue.at(11.f, [=](){
		ent->move(-7.0f);
	}); 
}

TTFB_MainScene::~TTFB_MainScene(){
}

void TTFB_MainScene::update(Step * _step){
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