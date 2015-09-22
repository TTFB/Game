#pragma once

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>

class PerspectiveCamera;
class MousePerspectiveCamera;

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
class BulletRagdoll;
class ComponentShaderText;
class TextureColourTable;

class Room;

class TTFB_MainScene : public Scene{
public:

	TTFB_EventQueue eventQueue;

	Room * room;
	
	Shader * screenSurfaceShader;
	RenderSurface * screenSurface;
	StandardFrameBuffer * screenFBO;
	
	ComponentShaderBase * baseShader;
	ComponentShaderBase * characterShader;
	ComponentShaderText * textShader;

	BulletWorld * bulletWorld;
	BulletDebugDrawer * debugDrawer;
	
	MousePerspectiveCamera * playerCam;
	BulletMeshEntity * playerEntity;
	glm::vec3 lastPos;
	TextureColourTable * playerPalette;

	MeshEntity * tilemapContour;
	
	Sprite * mouseIndicator;
	Sprite * crosshair;
	MousePerspectiveCamera * debugCam;

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	UILayer uiLayer;

	TTFB_MainScene(Game * _game);
	~TTFB_MainScene();
};