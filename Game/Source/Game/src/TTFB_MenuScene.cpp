#pragma 

#include <TTFB_MenuScene.h>
#include <RenderSurface.h>
#include <StandardFrameBuffer.h>
#include <shader/ComponentShaderText.h>
#include <Font.h>
#include <shader/ShaderComponentMVP.h>
#include <shader/ShaderComponentDiffuse.h>
#include <shader/ShaderComponentTexture.h>
#include <MousePerspectiveCamera.h>
#include <System.h>
#include <TTFB_ResourceManager.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Game.h>
#include <TextArea.h>
#include <RenderOptions.h>
#include <Resource.h>
#include <PointLight.h>
#include <MouseCameraController.h>
#include <TTFB_Controller.h>
#include <TTFB_Game.h>
#include <OpenALSound.h>
#include <TTFB_Constants.h>


TTFB_MenuScene::TTFB_MenuScene(Game* _game)  :
	TTFB_Scene(_game),
	screenSurfaceShader(new Shader("assets/engine basics/DefaultRenderSurface", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true)),
	baseShader(new ComponentShaderBase(true)),
	characterShader(new ComponentShaderBase(true)),
	textShader(new ComponentShaderText(true)),
	uiLayer(0,0,0,0),
	font(new Font("assets/engine basics/OpenSans-Regular.ttf", 32, true)),
	musicPlaying(false),
	music(nullptr)
{

	bulletWorld = new BulletWorld();
	
	baseShader->addComponent(new ShaderComponentMVP(baseShader)); 
	baseShader->addComponent(new ShaderComponentDiffuse(baseShader));
	baseShader->addComponent(new ShaderComponentTexture(baseShader));
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

	activeCamera = debugCam;
	
	// remove initial camera
	childTransform->removeChild(cameras.at(0)->parents.at(0));
	delete cameras.at(0)->parents.at(0);
	cameras.pop_back();

	//
	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);

	NodeUI * logo = new NodeUI(bulletWorld);
	logo->setRationalWidth(1);
	logo->setRationalHeight(1);
	logo->background->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("titleScreen")->texture);
	uiLayer.addChild(logo);

	introScreen = new NodeUI(bulletWorld);
	introScreen->setRationalWidth(1);
	introScreen->setRationalHeight(1);
	introScreen->background->mesh->pushTexture2D(TTFB_ResourceManager::scenario->getTexture("introScreen")->texture);
	uiLayer.addChild(introScreen);
	introScreen->setVisible(false);

	PointLight * light2 = new PointLight(glm::vec3(1, 1, 1),  0.01f, 0.001f, -1.f);
	lights.push_back(light2);
	childTransform->addChild(light2);
	light2->firstParent()->translate(0, 0, -5);

	camController = new MouseCameraController(debugCam);

	music = TTFB_ResourceManager::scenario->getAudio("openingMusic")->sound;
	music->setGain(0.2f);

	introSpeech = TTFB_ResourceManager::scenario->getAudio("introDialogue")->sound;
	introSpeech->setGain(2.f);
}

TTFB_MenuScene::~TTFB_MenuScene() {
	music->stop();
	introSpeech->stop();
	deleteChildTransform();
	baseShader->safeDelete();
	characterShader->safeDelete();
	textShader->safeDelete();

	screenSurface->safeDelete();
	//screenSurfaceShader->safeDelete();
	screenFBO->safeDelete();
}

void TTFB_MenuScene::update(Step* _step) {

	if(!musicPlaying) {
		music->play(true);
		musicPlaying = true;
	}

	bulletWorld->update(_step);

	glm::uvec2 sd = sweet::getScreenDimensions();
	uiLayer.resize(0, sd.x, 0, sd.y);

	uiLayer.update(_step);

	if(keyboard->keyJustDown(GLFW_KEY_F12)){
		game->toggleFullScreen();
	}

	if(keyboard->keyJustDown(GLFW_KEY_1)){
		cycleCamera();
	}

	debugCam->update(_step);

	camController->update(_step);

	if((controller->IsConnected() && controller->specialFireButton.justDown()) || keyboard->keyJustUp(GLFW_KEY_P)) {
		if(introScreen->isVisible()){
			controller->clearBindings();
			((TTFB_Game *)game)->switchToScene(SPAMALOT);
			return;
		}else {
			introScreen->setVisible(true);
			introSpeech->play();
		}
	}
	Scene::update(_step);
}

void TTFB_MenuScene::render(sweet::MatrixStack* _matrixStack, RenderOptions* _renderOptions) {
	_renderOptions->clear();
	screenFBO->resize(game->viewPortWidth, game->viewPortHeight);
	//Bind frameBuffer
	screenFBO->bindFrameBuffer();
	//render the scene to the buffer
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Scene::render(_matrixStack, _renderOptions);

	//Render the buffer to the render surface
	screenSurface->render(screenFBO->getTextureId());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	uiLayer.render(_matrixStack, _renderOptions); 
}

void TTFB_MenuScene::load() {
	Scene::load();
}

void TTFB_MenuScene::unload() {
	Scene::unload();
}