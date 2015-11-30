#pragma once

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>

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

class TTFB_StageScene : public Scene{
public:

	int score;

	TTFB_EventQueue eventQueue;
	
	Shader * screenSurfaceShader;
	RenderSurface * screenSurface;
	StandardFrameBuffer * screenFBO;
	
	ComponentShaderBase * baseShader;
	ComponentShaderBase * characterShader;
	ComponentShaderText * textShader;

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

	UILayer uiLayer;

	TTFB_Stage * stage;

	TTFB_Controller * controller;
	TTFB_Audience * audience;

	ParticleSystem * fireSystem;
	Particle * fireParticle;

	Sprite * fog;

	bool fireActive;
	bool fogActive;
	bool fadeOutLights;
	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	virtual TTFB_Actor * createActor(std::string _name);
	virtual void endScene(std::string _sceneKey);
	virtual TTFB_Prop * addProp(std::string _samplerResourceId, glm::vec3 _pos);
	virtual TTFB_SetPiece * addSetPiece(std::string _samplerResourceId, glm::vec3 _pos);

	void addFog();
	void toggleFog();

	TTFB_StageScene(Game * _game, float _stageWidth, std::string _floorTex, std::string _sideTex, std::string _backTex, std::string _topTex, std::string _frontTex);
	~TTFB_StageScene();
};