#pragma once

#include <TTFB_Entity.h>
#include <Entity.h>
#include <Box2DMeshEntity.h>
#include <Rectangle.h>

class MeshEntity;

class TTFB_Stage : public Entity{
public:	

	 Box2DMeshEntity * stageBase;
	 Sprite			 * stageBack;
	 Sprite			 * stageFrontLeft;
	 Sprite			 * stageFrontRight;
	 Sprite			 * stageBottom;
	 Sprite			 * stageTop;
	 Sprite			 * curtainLeft;
	 Sprite			 * curtainRight;

	TTFB_Stage();
	~TTFB_Stage();

	sweet::Rectangle getVisibleBounds() const;
};