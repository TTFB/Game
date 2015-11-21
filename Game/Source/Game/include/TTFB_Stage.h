#pragma once

#include <TTFB_Entity.h>
#include <Entity.h>
#include <Box2DMeshEntity.h>
#include <Rectangle.h>

class MeshEntity;

class TTFB_Stage : public Entity{
public:	

	 Box2DMeshEntity * stageBase;
	 MeshEntity		 * stageBack;
	 MeshEntity		 * stageFrontLeft;
	 MeshEntity		 * stageFrontRight;
	 MeshEntity		 * stageBottom;
	 MeshEntity		 * stageTop;

	TTFB_Stage(float _width, Box2DWorld * _world, std::string _floorTex, std::string _sideTex, std::string _backTex, std::string _stageTop, std::string _stageBottom, Shader * _shader = nullptr);
	~TTFB_Stage();

	void setShader(Shader * _shader);
	sweet::Rectangle getVisibleBounds();


private:
	float width;
};