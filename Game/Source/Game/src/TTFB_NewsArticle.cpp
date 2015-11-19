#pragma once

#include <TTFB_NewsArticle.h>
#include <TTFB_Constants.h>
#include <TTFB_ResourceManager.h>

TTFB_NewsArticle::TTFB_NewsArticle(Shader * _shader, std::string _play, int _score) :
	NodeUI(nullptr),
	soundPlayed(false)
{
	if(_play == BLACK_KNIGHT) {
		switch(_score) {
			case 1: 
				article = TTFB_ResourceManager::scenario->getTexture("black_knight_one_star")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("black_knight_one_star_sound")->sound;
				break;
			case 2:
				article = TTFB_ResourceManager::scenario->getTexture("black_knight_two_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("black_knight_two_stars_sound")->sound;
				break;
			case 3:
				article = TTFB_ResourceManager::scenario->getTexture("black_knight_three_stars")->texture;
				sound   = TTFB_ResourceManager::scenario->getAudio("black_knight_two_stars_sound")->sound;
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
	background->mesh->pushTexture2D(article);
}

void TTFB_NewsArticle::update(Step* _step) {
	if(!soundPlayed) {
		sound->play();	
		soundPlayed = true;
	}

	firstParent()->rotate(2.f, 0.f, 0.f, 1.f, kWORLD);
	NodeUI::update(_step);
}