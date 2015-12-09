#pragma once

#include <Scene.h>
#include <UILayer.h>
#include <BulletDebugDrawer.h>
#include <BulletWorld.h>
#include <TTFB_EventQueue.h>
#include <TTFB_StageScene.h>
#include <TTFB_DialoguePlayer.h>
#include <OpenALSound.h>
#include <map>
#include <string>

class TTFB_DraculaScene : public TTFB_StageScene{
public:

	TTFB_EventQueue eventQueue;

	TTFB_Actor * dracula;
	TTFB_Actor * renfeild;

	TTFB_DialoguePlayer * dialoguePlayer;

	OpenAL_Sound * backgroundMusic;

	std::map<std::string, bool> conditions;

	double lastFireEmission;

	bool bgMusicStarted;
	float startSceneDelay;
	
	TTFB_DraculaScene(Game * _game);
	~TTFB_DraculaScene();

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;
};