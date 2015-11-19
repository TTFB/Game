#pragma once

#include <Scene.h>

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>

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


class TTFB_MenuScene : public Scene {
public:

	Shader * screenSurfaceShader;
	RenderSurface * screenSurface;
	StandardFrameBuffer * screenFBO;
	
	ComponentShaderBase * baseShader;
	ComponentShaderBase * characterShader;
	ComponentShaderText * textShader;

	BulletWorld * bulletWorld;
	
	MousePerspectiveCamera * playerCam;

	MousePerspectiveCamera * debugCam;
	MouseCameraController * camController;

	MeshEntity * cheese;
	
	Font * font;

	UILayer uiLayer;

	TTFB_Stage * stage;

	TTFB_Controller * controller;

	Sprite * mouseIndicator;

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	TTFB_MenuScene(Game * _game);
	~TTFB_MenuScene();
};