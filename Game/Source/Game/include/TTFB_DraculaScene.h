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
	TTFB_Actor * renfield;

	TTFB_Prop * wineProp;

	TTFB_SetPiece * setPeiceBuilding;
	TTFB_SetPiece * setPeiceBuildingForeground;
	TTFB_SetPiece * setPieceWeb;
	TTFB_SetPiece * setPieceBed;
	TTFB_SetPiece * setPieceFireplace;
	TTFB_SetPiece * setPieceLuggage;
	TTFB_SetPiece * setPieceLease;

	TTFB_DialoguePlayer * dialoguePlayer;

	OpenAL_Sound * backgroundMusic;
	OpenAL_Sound * clapping;

	std::map<std::string, bool> conditions;

	double lastFireEmission;

	bool bgMusicStarted;
	float startSceneDelay;
	TTFB_Prop* lease;
	TTFB_DraculaScene(Game * _game);
	~TTFB_DraculaScene();

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;

	void endScene();
};