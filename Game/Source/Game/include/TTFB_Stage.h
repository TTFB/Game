#pragma once

#include <TTFB_Entity.h>
#include <Entity.h>
#include <Box2DMeshEntity.h>

class MeshEntity;

class TTFB_Stage : public Entity{
public:	

	 Box2DMeshEntity * stageBase;
	 MeshEntity		 * stageBack;
	 MeshEntity		 * stageFrontLeft;
	 MeshEntity		 * stageFrontRight;

	TTFB_Stage(float _width, Box2DWorld * _world, std::string _floorTex, std::string _sideTex, std::string _backTex, Shader * _shader = nullptr);
	~TTFB_Stage();

	void setShader(Shader * _shader);

private:
	float width;
};