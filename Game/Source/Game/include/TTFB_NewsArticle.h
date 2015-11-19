#pragma once

#include <Sprite.h>
#include <NodeUI.h>
#include <OpenALSound.h>
#include <Texture.h>

class TTFB_NewsArticle : public NodeUI {
public:

	TTFB_NewsArticle(Shader * _shader, std::string _play, int _score);

	virtual void update(Step * _step) override; 

private:
	Texture * article; 
	OpenAL_Sound * sound;
	bool soundPlayed;
};