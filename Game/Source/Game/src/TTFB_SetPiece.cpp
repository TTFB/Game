#pragma once

#include <TTFB_SetPiece.h>
#include <TTFB_ResourceManager.h>
#include <TTFB_Actor.h>

TTFB_SetPiece::TTFB_SetPiece(Box2DWorld* _world, std::string _samplerResourceId, Shader* _shader, sweet::Rectangle _stageBounds) :
	Box2DSprite(_world, TTFB_ResourceManager::scenario->getTextureSampler(_samplerResourceId)->textureSampler),
	raiseDir(0),
	stageBounds(_stageBounds)
{
	b2Filter filt;
	filt.categoryBits = Category::SET_PIECE;
	filt.maskBits     = 0x000000 | Category::BOUNDARY;

	setShader(_shader);
	scale = 0.01f;
	createFixture(filt);
	body->SetGravityScale(0.0f);
}

void TTFB_SetPiece::update(Step* _step) {
	if(stageBounds.getTopLeft().y + 10 < body->GetPosition().y + getCorrectedHeight() * 0.5f) {
		raiseDir = 0;
	}
	if(stageBounds.getBottomLeft().y >= body->GetPosition().y - getCorrectedHeight() * 0.5f) {
		raiseDir = 0;
	}
	setTranslationPhysical(0.0f, 0.1f * raiseDir, 0.0f, true);
	Box2DSprite::update(_step);
}

void TTFB_SetPiece::raise() {
	raiseDir = 1;
}

void TTFB_SetPiece::lower() {
	raiseDir = -1;
}