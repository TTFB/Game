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

	if(_score <= -1500) {
		_score = 1;
	}else if(_score > -1500 && _score < 1500){
		_score = 2;
	}else {
		_score = 3;
	}

	if(_play == SPAMALOT) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTextureSampler("spamalot_one_star")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTextureSampler("spamalot_two_stars")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTextureSampler("spamalot_three_stars")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("spamalot_two_stars_sound")->sound;
				break;
			default:
				throw "Bad score";
		}
	}else if(_play == GRINCH) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTextureSampler("grinch_one_star")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTextureSampler("grinch_two_stars")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTextureSampler("grinch_three_stars")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("grinch_two_stars_sound")->sound;
				break;
			default:
				throw "Bad score";
		}
	}else if(_play == DRACULA) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTextureSampler("dracula_one_star")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("dracula_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTextureSampler("dracula_two_stars")->textureSampler->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("dracula_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTextureSampler("dracula_three_stars")->textureSampler->texture;
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
	firstParent()->translate(-350, -650, 0.f);

}

void TTFB_NewsArticle::update(Step* _step) {
	if(!soundPlayed) {
		sound->play();	
		soundPlayed = true;
	}

	if(scale < 2.f) {
		scale += 0.05f;
		container->rotate(18.f, 0.f, 0.f, 1.f, kWORLD);
		container->scale(scale, false);
	}

	NodeUI::update(_step);
}