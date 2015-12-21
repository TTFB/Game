#pragma once

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>
#include <TTFB_Scene.h>
#include "TTFB_Fog.h"
#include <TextArea.h>
#include "TTFB_NewsArticle.h"
#include <string>

class TTFB_SetPiece;
class TTFB_Prop;
class TTFB_Audience;
class TTFB_Controller;
class PerspectiveCamera;
class MousePerspectiveCamera;
class MouseCameraController;

class Box2DWorld;
class Box2DDebugDrawer;
class Box2DMeshEntity;
class MeshEntity;

class ShaderComponentHsv;

class Shader;
class RenderSurface;
class StandardFrameBuffer;
class Material;
class Sprite;

class PointLight;

class BulletMeshEntity;
class ComponentShaderText;

class Font;

class TTFB_Stage;
class TTFB_Actor;

class ParticleSystem;
class Particle;

class TTFB_StageScene : public TTFB_Scene{
public:

	int score;
	int lastScore;
	int scoreQueue;

	int countDownSec;
	float countDownScaler;
	float countDownAcc;
	Transform * countDownTextCont;

	bool sceneEnded;
	bool showingNewsPaper;

	NodeUI * endMessage;
	OpenAL_Sound * endSound;
	bool endAudioPlayed;

	TTFB_EventQueue eventQueue;
	
	Shader * screenSurfaceShader;
	RenderSurface * screenSurface;
	StandardFrameBuffer * screenFBO;
	
	ComponentShaderBase * baseShader;
	ComponentShaderBase * characterShader;
	ComponentShaderText * textShader;
	ComponentShaderText * countdownTextShader;

	BulletWorld * bulletWorld;
	BulletDebugDrawer * debugDrawer;
	
	MousePerspectiveCamera * playerCam;
	PerspectiveCamera * stageCam;
	
	Sprite * mouseIndicator;
	Sprite * crosshair;

	MousePerspectiveCamera * debugCam;
	MouseCameraController * camController;

	Box2DWorld * box2dWorld;
	Box2DDebugDrawer * box2dDebug;
	
	Font * font;
	Font * scoreFont;
	Font * countDownFont;

	UILayer uiLayer;

	TTFB_Stage * stage;

	TTFB_Audience * audience;

	ParticleSystem * fireSystem;
	Particle * fireParticle;

	TTFB_Fog * fog;

	TextArea * scoreText;
	TextArea * countDownText;

	bool fireActive;
	bool lastFireActive;

	bool fogActive;
	bool fadeOutLights;
	bool dimmingLights;
	
	ComponentShaderText* scoreTextShader;
	
	double fireTimer;
	float scoreScaler;
	
	TTFB_NewsArticle* newsArticle;

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	virtual TTFB_Actor * createActor(std::string _name);
	virtual void endScene(std::string _currentScene, std::string _nextScene, std::string _message, std::string audio);
	virtual TTFB_Prop * addProp(std::string _samplerResourceId, glm::vec3 _pos, float _scale = 1.0f);
	virtual TTFB_SetPiece * addSetPiece(std::string _samplerResourceId, glm::vec3 _pos, float _scaleMultiplier = 1.0f);

	void addFog();
	void toggleFog();

	void dimHouseLights();

	void incScore(int _score = 100);
	void decScore(int _score = 100);

	void countDown(int seconds);

	void setStage(TTFB_Stage * _stage);

	void addAudience(std::string _prefix);

	TTFB_StageScene(Game * _game);
	~TTFB_StageScene();

private:
	std::string pendingScene;
};