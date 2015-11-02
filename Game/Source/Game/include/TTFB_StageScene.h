#pragma once

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>

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

class TTFB_StageScene : public Scene{
public:

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

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	virtual TTFB_Actor * createActor(std::string _name);

	TTFB_StageScene(Game * _game, float _stageWidth);
	~TTFB_StageScene();
};