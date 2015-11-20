#pragma once

#include <TTFB_StageScene.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Stage.h>
#include <TTFB_Audience.h>

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
#include <MouseCameraController.h>

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
#include <TTFB_Actor.h>
#include <TTFB_Stage.h>
#include <Box2DWorld.h>
#include <Box2DDebugDrawer.h>
#include <Font.h>
#include <TTFB_Controller.h>
#include <RenderOptions.h>
#include <TTFB_NewsArticle.h>
#include <TTFB_Constants.h>
#include <TTFB_Prop.h>

TTFB_StageScene::TTFB_StageScene(Game * _game, float _stageWidth, std::string _floorTex, std::string _sideTex, std::string _backTex, std::string _topTex, std::string _frontTex) :
	Scene(_game),
	screenSurfaceShader(new Shader("assets/engine basics/DefaultRenderSurface", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true)),
	baseShader(new ComponentShaderBase(true)),
	characterShader(new ComponentShaderBase(true)),
	textShader(new ComponentShaderText(true)),
	debugDrawer(nullptr),
	uiLayer(0,0,0,0),
	box2dWorld(new Box2DWorld(b2Vec2(0.f, -10.0f))),
	box2dDebug(box2dWorld->createDebugDrawer()),
	font(new Font("assets/engine basics/OpenSans-Regular.ttf", 100, true)),
	controller(new TTFB_Controller()),
	score(1)
{
	baseShader->addComponent(new ShaderComponentMVP(baseShader)); 
	baseShader->addComponent(new ShaderComponentDiffuse(baseShader));
	ShaderComponentTexture * texComp = new ShaderComponentTexture(baseShader);
	texComp->alphaDiscardThreshold = 0.05f;
	baseShader->addComponent(texComp);
	baseShader->compileShader();

	textShader->textComponent->setColor(glm::vec3(0.0f, 0.0f, 0.0f));

	//Set up debug camera
	debugCam = new MousePerspectiveCamera();
	cameras.push_back(debugCam);
	childTransform->addChild(debugCam);
	debugCam->farClip = 1000.f;
	debugCam->childTransform->rotate(90, 0, 1, 0, kWORLD);
	debugCam->parents.at(0)->translate(5.0f, 1.5f, 22.5f);
	debugCam->yaw = 90.0f;
	debugCam->pitch = -10.0f;
	debugCam->speed = 1;

	stageCam = new PerspectiveCamera();
	cameras.push_back(stageCam);
	childTransform->addChild(stageCam);
	stageCam->firstParent()->translate(0.0f, 15.f, 29.598f);
	stageCam->yaw = 90.0f;
	stageCam->pitch = -7.f;
	activeCamera = stageCam;
	
	// remove initial camera
	//childTransform->removeChild(cameras.at(0)->parents.at(0));
	//delete cameras.at(0)->parents.at(0);
	//cameras.pop_back();

	//
	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);

	// mouse cursor
	mouseIndicator = new Sprite();
	uiLayer.childTransform->addChild(mouseIndicator);
	mouseIndicator->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("CURSOR")->texture);
	mouseIndicator->parents.at(0)->scale(32, 32, 1);
	mouseIndicator->mesh->scaleModeMag = GL_NEAREST;
	mouseIndicator->mesh->scaleModeMin = GL_NEAREST;

	for(unsigned long int i = 0; i < mouseIndicator->mesh->vertices.size(); ++i){
		mouseIndicator->mesh->vertices[i].x += 0.5f;
		mouseIndicator->mesh->vertices[i].y -= 0.5f;
	}

	mouseIndicator->mesh->dirty = true;
	mouseIndicator->setShader(uiLayer.shader, true);

	stage = new TTFB_Stage(_stageWidth, box2dWorld, _floorTex, _sideTex, _backTex, _topTex, _frontTex, baseShader);
	childTransform->addChild(stage);

	audience = new TTFB_Audience(baseShader);
	//childTransform->addChild(audience)->translate(0.f, 17.f, 20.0f);
	//audience->firstParent()->scale(25.0f);

	// Add the debug drawer last so it appears on top
	childTransform->addChild(box2dDebug, true);

	camController = new MouseCameraController(debugCam);

	box2dDebug->drawing = false;
}

TTFB_StageScene::~TTFB_StageScene(){
	deleteChildTransform();
	baseShader->safeDelete();
	characterShader->safeDelete();
	textShader->safeDelete();

	screenSurface->safeDelete();
	//screenSurfaceShader->safeDelete();
	screenFBO->safeDelete();
	delete debugDrawer;
}


void TTFB_StageScene::update(Step * _step){

	// Toggle debug drawer
	if(keyboard->keyJustUp(GLFW_KEY_2)){
		box2dDebug->drawing = !box2dDebug->drawing;
	}

	if(keyboard->keyJustUp(GLFW_KEY_1)){
		cycleCamera();
	}

	box2dWorld->update(_step);

	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);

	uiLayer.update(_step);

	mouseIndicator->parents.at(0)->translate(mouse->mouseX(), mouse->mouseY(), 0, false);

	if(keyboard->keyJustDown(GLFW_KEY_F12)){
		game->toggleFullScreen();
	}

	if(keyboard->keyJustDown(GLFW_KEY_1)){
		cycleCamera();
	}

	debugCam->update(_step);
	camController->update(_step);

	controller->update(_step);

	Scene::update(_step);
}

void TTFB_StageScene::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){

	glEnable(GL_DEPTH_TEST);
	_renderOptions->depthEnabled = true;
	screenFBO->resize(game->viewPortWidth, game->viewPortHeight);
	//Bind frameBuffer
	screenFBO->bindFrameBuffer();
	//render the scene to the buffer

	//_renderOptions->depthEnabled = false;
	_renderOptions->clear();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Scene::render(_matrixStack, _renderOptions);

	//Render the buffer to the render surface
	screenSurface->render(screenFBO->getTextureId());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	uiLayer.render(_matrixStack, _renderOptions);
}

void TTFB_StageScene::load(){
	Scene::load();	

	screenSurface->load();
	screenFBO->load();
	uiLayer.load();
}

void TTFB_StageScene::unload(){
	uiLayer.unload();
	screenFBO->unload();
	screenSurface->unload();

	Scene::unload();	
}

TTFB_Actor * TTFB_StageScene::createActor(std::string _name) {
	return new TTFB_Actor(_name, box2dWorld, bulletWorld, font, textShader, baseShader);
}

void TTFB_StageScene::endScene(std::string _sceneKey) {
	
	TTFB_NewsArticle * testArticle = new TTFB_NewsArticle(baseShader, _sceneKey, score);
	
	VerticalLinearLayout * articleContainer = new VerticalLinearLayout(bulletWorld);
	articleContainer->horizontalAlignment = kCENTER;
	articleContainer->verticalAlignment = kMIDDLE;
	articleContainer->setRationalWidth(1, &uiLayer);
	articleContainer->setRationalHeight(1, &uiLayer);

	articleContainer->addChild(testArticle);
	testArticle->firstParent()->translate(testArticle->getWidth()/2, testArticle->getHeight()/2, 0);

	uiLayer.addChild(articleContainer);
}

TTFB_Prop * TTFB_StageScene::addProp(std::string _samplerResourceId, glm::vec3 _pos) {
	TTFB_Prop * prop = new TTFB_Prop(box2dWorld, _samplerResourceId, baseShader);
	childTransform->addChild(prop);
	prop->setTranslationPhysical(_pos);
	return prop;
}