#pragma once

#include <TTFB_SetPiece.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>
#include <TTFB_Constants.h>

TTFB_SetPiece::TTFB_SetPiece(Box2DWorld* _world, std::string _samplerResourceId, Shader* _shader, sweet::Rectangle _stageBounds, float _scaleMultiplier) :
	Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_samplerResourceId)->textureSampler),
	raiseDir(0),
	stageBounds(_stageBounds),
	forceFrame(false),
	lowered(false),
	raised(true)
{
	b2Filter filt;
	filt.categoryBits = Category::SET_PIECE;
	filt.maskBits     = 0x000000 | Category::BOUNDARY;

	setShader(_shader);
	scale = B2_SCALE * _scaleMultiplier;
	createFixture(filt);
	body->SetGravityScale(0.0f);
}

void TTFB_SetPiece::update(Step* _step) {
	setTranslationPhysical(0.0f, 0.1f * raiseDir, 0.0f, true);
	if(!forceFrame){
		if(stageBounds.getTopLeft().y + 10 < body->GetPosition().y - getCorrectedHeight() * 0.5f) {
			raiseDir = 0;
			raised = true;
			lowered = false;
		}
		if(stageBounds.getBottomLeft().y >= body->GetPosition().y - getCorrectedHeight() * 0.5f) {
			raiseDir = 0;
			raised = false;
			lowered = true;
		}
	}

	if(raiseDir != 0) {
		raised = false;
		lowered = false;
	}

	forceFrame = false;
	Box2DSprite::update(_step);
}

void TTFB_SetPiece::raise() {
	raiseDir = 1;
}

void TTFB_SetPiece::lower() {
	raiseDir = -1;
}

bool TTFB_SetPiece::isLowered() {
	return lowered;
}

bool TTFB_SetPiece::isRaised() {
	return raised;
}

void TTFB_SetPiece::toggle() {
	if(stageBounds.getTopLeft().y + 10 < body->GetPosition().y + getCorrectedHeight() * 0.5f || raiseDir == 1) {
		raiseDir = -4;	
	}else {
		raiseDir = 4;
	}
	forceFrame = true;
}