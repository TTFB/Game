#pragma once

#include <Sprite.h>

class TTFB_Audience : public Sprite {
public:

	TTFB_Audience(Shader * _shader);
	~TTFB_Audience();

	void update(Step * _step) override;
};