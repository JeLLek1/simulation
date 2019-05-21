#include "pch.h"
#include "AnimationHandler.h"

unsigned int AnimationHandler::returnStep()
{
	return this->currentStep;
}

void AnimationHandler::update(const float dt)
{
	if (this->updateTimeLast + dt >= this->updateTime) {
		this->updateTimeLast = dt;
		this->currentStep++;
		if (this->currentStep >= AnimationHandler::MAX_STEP)
			this->currentStep -= AnimationHandler::MAX_STEP;
	}
	else {
		this->updateTimeLast += dt;
	}
	return;
}

AnimationHandler::AnimationHandler(const float updateTime)
{
	this->currentStep = 0;
	this->updateTime = updateTime;
	this->updateTimeLast = 0;
}


AnimationHandler::~AnimationHandler()
{
}
