#pragma once
#include "StaticObject.h"
class StaticObjectResouces : public StaticObject
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);

	StaticObjectResouces();
	~StaticObjectResouces();
};

