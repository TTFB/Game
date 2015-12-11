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
#include <shader\ShaderComponentDepthOffset.h>

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
#include <TTFB_SetPiece.h>

#include <ParticleSystem.h>
#include <Particle.h>
#include <TTFB_Game.h>
#include <TextArea.h>

TTFB_StageScene::TTFB_StageScene(Game * _game, float _stageWidth, std::string _floorTex, std::string _sideTex, std::string _backTex, std::string _topTex, std::string _frontTex) :
	TTFB_Scene(_game),
	score(0),
	scoreQueue(0),
	screenSurfaceShader(new Shader("assets/engine basics/DefaultRenderSurface", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true)),
	baseShader(new ComponentShaderBase(true)),
	characterShader(new ComponentShaderBase(true)),
	textShader(new ComponentShaderText(true)),
	debugDrawer(nullptr),
	box2dWorld(new Box2DWorld(b2Vec2(0.f, -10.0f))),
	box2dDebug(box2dWorld->createDebugDrawer()),
	font(new Font("assets/engine basics/OpenSans-Regular.ttf", 100, true)),
	uiLayer(0,0,0,0),
	fireActive(false),
	fadeOutLights(false),
	dimmingLights(false),
	scoreTextShader(new ComponentShaderText(true)),
	fireTimer(0),
	scoreScaler(0.0f)
{
	scoreFont = TTFB_ResourceManager::scenario->getFont("bebas")->font;

	baseShader->addComponent(new ShaderComponentMVP(baseShader)); 
	baseShader->addComponent(new ShaderComponentDiffuse(baseShader));
	ShaderComponentTexture * texComp = new ShaderComponentTexture(baseShader);
	texComp->alphaDiscardThreshold = 0.05f;
	baseShader->addComponent(texComp);
	baseShader->addComponent(new ShaderComponentDepthOffset(baseShader));
	baseShader->compileShader();

	textShader->textComponent->setColor(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);

	VerticalLinearLayout * container = new VerticalLinearLayout(bulletWorld);
	container->setRationalWidth(1.0f);
	container->setRationalHeight(1.0f);

	HorizontalLinearLayout * scoreLayout = new HorizontalLinearLayout(bulletWorld);
	scoreLayout->horizontalAlignment = kCENTER;
	scoreLayout->verticalAlignment = kTOP;
	scoreLayout->setRationalWidth(1.f);
	scoreLayout->setPadding(15.0f);
	scoreLayout->setPaddingTop(45.0f);
	scoreLayout->setBackgroundColour(0.05f, 0.05f, 0.05f, 0.7f);
	scoreLayout->boxSizing = kBORDER_BOX;

	scoreTextShader->setColor(1.f, 1.f, 1.f);
	scoreText = new TextArea(bulletWorld, scoreFont, scoreTextShader, 300);
	scoreText->horizontalAlignment = kCENTER;

	scoreLayout->addChild(scoreText);
	container->addChild(scoreLayout);
	uiLayer.addChild(container);

	scoreLayout->invalidateLayout();

	uiLayer.setRenderMode(kTEXTURE);
	uiLayer.invalidateLayout();

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
	childTransform->addChild(audience)->translate(0.f, 11.f, 20.0f);
	audience->firstParent()->scale(25.0f, 25.0f * 0.562f, 1.0f);

	// Add the debug drawer last so it appears on top
	childTransform->addChild(box2dDebug, true);

	camController = new MouseCameraController(debugCam);

	box2dDebug->drawing = false;

	fireSystem = new ParticleSystem(TTFB_ResourceManager::scenario->getTexture("blood")->texture, box2dWorld, 0);
	stage->childTransform->addChild(fireSystem);

	fireSystem->setShader(baseShader, true);

#pragma region LightSetup
	
	SpotLight * light0 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(0,0,0), 45.f, 0.1f, 0.001f, -1.f);
	lights.push_back(light0);
	childTransform->addChild(light0);
	light0->firstParent()->translate(20, 10, 13);
	
	SpotLight * light1 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.01f, 0.001f, -1.f);
	lights.push_back(light1);
	childTransform->addChild(light1);
	light1->firstParent()->translate(-20, 10, 13);

	SpotLight * light2 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.01f, 0.001f, -1.f);
	lights.push_back(light2);
	childTransform->addChild(light2);
	light2->firstParent()->translate(0, 10, 13);

	SpotLight * light3 = new SpotLight(glm::vec3(0, 0, -1), glm::vec3(1,1,1), 45.f, 0.01f, 0.001f, -1.f);
	lights.push_back(light3);
	childTransform->addChild(light3);
	light3->firstParent()->translate(20, 10, 13);

#pragma endregion 

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

	if(scoreQueue > 0) {
		score += 1;
		scoreQueue -= 1;
		scoreTextShader->setColor(102.0f/255.0f, 238.0f/255.0f, 87.0f/255.0f);
	}else if(scoreQueue < 0) {
		score -= 1;
		scoreQueue += 1;
		scoreTextShader->setColor(254.0/255.0f, 72.0/255.0f, 46.0/255.0f);
	}

	if(scoreScaler > 0.0005f || scoreScaler < -0.0005f) {
		float curScale = scoreText->firstParent()->getScaleVector().x;
		scoreText->firstParent()->scale(scoreScaler + curScale, scoreScaler + curScale, 1.0f, false);
		if(scoreScaler > 0.0005f) {
			scoreScaler -= 0.02;
		}else {
			scoreScaler += 0.02f;
		}
	}else {
		float curScale = scoreText->firstParent()->getScaleVector().x;
		if(curScale > 1.00005f) {
			scoreText->firstParent()->scale(curScale -0.02f, -0.02f + curScale, 1.0f, false);
		}else if(curScale < 0.99995f){
			scoreText->firstParent()->scale(0.02f + curScale, 0.02f + curScale, 1.0f, false);
		}
	}
	

	if(score != lastScore) {
		scoreText->setText(L"Score " + std::to_wstring(score));
		lastScore = score;
	}

	if(lastFireActive == false && fireActive == true) {
		fireTimer = 0;
		lastFireActive = true;
	}

	fireTimer += _step->deltaTime;

	if(fireTimer > 1.0) {
		fireActive = false;
		lastFireActive = false;
	}

	if(fadeOutLights) {

		lights[1]->setIntensities(lights[1]->getIntensities() - 0.05f);
		lights[2]->setIntensities(lights[2]->getIntensities() - 0.05f);
		lights[3]->setIntensities(lights[3]->getIntensities() - 0.05f);

		if(lights[1]->getIntensities().x <= 0 && lights[2]->getIntensities().x <= 0 && lights[3]->getIntensities().x <= 0) {
			fadeOutLights = false;
		}
	}

	if(dimmingLights) {
		
		if(lights[1]->getAmbientCoefficient() <= 0.0004) {
			dimmingLights = false;
		}else {
			lights[1]->setAmbientCoefficient(lights[1]->getAmbientCoefficient() - 0.0002);
			lights[2]->setAmbientCoefficient(lights[1]->getAmbientCoefficient() - 0.0002);
			lights[3]->setAmbientCoefficient(lights[1]->getAmbientCoefficient() - 0.0002);
		}
	}

	if(score <= -2000) {
		audience->setBored(3);
	}else if(score <= -1000) {
		audience->setBored(2);
	}else if(score <= -500) {
		audience->setBored(1);
	}else if(score > -500 && score < 500) {
		audience->setNeutral();
	}else if(score >= 500) {
		audience->setHappy(1);
	}else if(score >= 1000) {
		audience->setHappy(2);
	}else if(score >= 2000) {
		audience->setHappy(3);
	}

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
	articleContainer->verticalAlignment   = kMIDDLE;
	articleContainer->setRationalWidth(1, &uiLayer);
	articleContainer->setRationalHeight(1, &uiLayer);

	articleContainer->childTransform->addChild(testArticle->container);

	uiLayer.addChild(articleContainer);

	articleContainer->firstParent()->translate(uiLayer.getWidth()/2, uiLayer.getHeight()/2, 0, true);

	fadeOutLights = true;
}

TTFB_Prop * TTFB_StageScene::addProp(std::string _samplerResourceId, glm::vec3 _pos) {
	TTFB_Prop * prop = new TTFB_Prop(box2dWorld, _samplerResourceId, baseShader);
	childTransform->addChild(prop);
	prop->setTranslationPhysical(_pos);
	return prop;
}

TTFB_SetPiece * TTFB_StageScene::addSetPiece(std::string _samplerResourceId, glm::vec3 _pos) {
	TTFB_SetPiece * set = new TTFB_SetPiece(box2dWorld, _samplerResourceId, baseShader, stage->getVisibleBounds());
	childTransform->addChild(set);
	_pos.y = stage->getVisibleBounds().getTopLeft().y;
	set->setTranslationPhysical(_pos);
	return set;
}

void TTFB_StageScene::addFog() {
	fog = new TTFB_Fog(baseShader);
	childTransform->addChild(fog);
	fog->firstParent()->translate(0, 6.5, 2);
	fog->firstParent()->scale(50, -3, 1);
	fog->setVisible(false);
	if(controller->IsConnected()) {
		fog->setVisible((bool)controller->specialFogSwitch.currentState);
	}
}

void TTFB_StageScene::toggleFog() {
	fog->setVisible(!fog->isVisible());
	fogActive = fog->isVisible();
}

void TTFB_StageScene::incScore(int _score) {
	scoreQueue += _score;
	scoreScaler = 0.1f;
}

void TTFB_StageScene::decScore(int _score) {
	scoreQueue -= _score;
	scoreScaler = -0.1f;
}

void TTFB_StageScene::dimHouseLights() {
	dimmingLights = true;
}
