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

class TTFB_MainScene : public TTFB_StageScene{
public:

	TTFB_EventQueue eventQueue;

	TTFB_Actor * kingArthur;
	TTFB_Actor * blackKnight;

	TTFB_SetPiece * setPieceTree1;//tree
	TTFB_SetPiece * setPieceTree2;//tree2
	TTFB_SetPiece * setPieceBush;//bush
	TTFB_SetPiece * setPieceMatte;//matte

	ParticleSystem * leftArmBlood;
	ParticleSystem * rightArmBlood;
	ParticleSystem * leftLegBlood;
	ParticleSystem * rightLegBlood;

	TTFB_DialoguePlayer * dialoguePlayer;

	OpenAL_Sound * backgroundMusic;

	std::map<std::string, bool> conditions;

	bool bgMusicStarted;
	float startSceneDelay;

	virtual void update(Step * _step) override;
	virtual void render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	
	virtual void load() override;
	virtual void unload() override;
	
	void leftArmBleed();
	void rightArmBleed();
	void leftLegBleed();
	void rightLegBleed();

	void stopLeftArmBleeding();
	void stopRightArmBleeding();
	void stopLeftLegBleeding();
	void stopRightLegBleeding();

	TTFB_MainScene(Game * _game);
	~TTFB_MainScene();
};