#pragma once
#include "SpriteDividedMenager.h"
class StaticObject
{
public:
	unsigned char partNumber;
	TextureNames texname;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
};

