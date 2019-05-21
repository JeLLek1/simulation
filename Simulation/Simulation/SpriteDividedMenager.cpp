#include "pch.h"
#include "SpriteDividedMenager.h"

void SpriteDividedMenager::loadSprite(const TextureNames& name, sf::Texture* texture, sf::Vector2u partSize, unsigned char partLenght, bool centerBottom) {
	SpriteDivided* temp = new SpriteDivided;
	temp->setTexture(*texture);
	temp->partLenght = partLenght;
	temp->partSize = partSize;
	if (centerBottom)
		temp->setOrigin(sf::Vector2f(static_cast<float>(partSize.x) / 2, static_cast<float>(partSize.y) / 2));
	else
		temp->setOrigin(sf::Vector2f(static_cast<float>(partSize.x) / 2, static_cast<float>(partSize.y)));

	this->sprites.insert(std::pair<TextureNames, SpriteDivided*>(name, temp));

}
SpriteDivided* SpriteDividedMenager::getRef(const TextureNames & name) {
	return this->sprites.at(name);
}

void SpriteDividedMenager::update(const float dt)
{
	this->animationHandler->update(dt);
	return;
}

unsigned int SpriteDividedMenager::returnAnimationStep()
{
	return this->animationHandler->returnStep();
}

SpriteDividedMenager::SpriteDividedMenager()
{
	this->animationHandler = new AnimationHandler(0.25);
}

SpriteDividedMenager::~SpriteDividedMenager()
{
	delete animationHandler;
}
