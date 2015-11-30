#pragma once

#include <TTFB_NewsArticle.h>
#include <TTFB_Constants.h>
#include <Transform.h>
#include <TTFB_ResourceManager.h>

TTFB_NewsArticle::TTFB_NewsArticle(Shader * _shader, std::string _play, int _score) :
	NodeUI(nullptr),
	soundPlayed(false),
	scale(1.0f)
{
	if(_play == SPAMALOT) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTexture("spamalot_one_star")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTexture("spamalot_two_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTexture("spamalot_three_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_two_stars_sound")->sound;
				break;
			default:
				throw "Bad score";
		}
	}else if(_play == GRINCH) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTexture("grinch_one_star")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTexture("grinch_two_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTexture("grinch_three_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_two_stars_sound")->sound;
				break;
			default:
				throw "Bad score";
		}
	}else if(_play == DRACULA) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTexture("dracula_one_star")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("dracula_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTexture("dracula_two_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("dracula_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTexture("dracula_three_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("dracula_two_stars_sound")->sound;
				break;
			default:
				throw "Bad score";
		}
	}else {
		throw "Bad play name";
	}

	container = new Transform();

	container->addChild(this);

	background->mesh->pushTexture2D(article);
	setPixelWidth(800);
	setPixelHeight(1000);
	firstParent()->translate(-400, -500, 0.f);
}

void TTFB_NewsArticle::update(Step* _step) {
	if(!soundPlayed) {
		sound->play();	
		soundPlayed = true;
	}

	if(scale < 1.8f) {
		scale += 0.05f;
		container->rotate(1.9f, 0.f, 0.f, 1.f, kWORLD);
		container->scale(scale, false);
	}

	NodeUI::update(_step);
}