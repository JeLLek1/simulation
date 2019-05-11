#include "pch.h"
#include "Man.h"



void Man::draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite, float dt, unsigned int mapWidth)
{
	ManManager* manMgr = new ManManager();
	this->update(dt);
	if (manMgr->isCorrect(simView, this->currentPosition, map))
	{
		sprite->setTextureRect(sf::IntRect((manMgr->direction(this->currentPosition, this->destination)) * sprite->partSize.x,
							   sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
		sprite->setPosition(Simulation::cartToIso(this->currentPosition, mapWidth));
		window->draw(*sprite);
	}
}

void Man::update(float dt)
{
	if (this->currentPosition == this->destination)
		this->destination = sf::Vector2f(this->manAi->getNextStep());
	else
	{
		this->currentPosition = sf::Vector2f((this->destination.x - this->currentPosition.x) / 10.f, (this->destination.y - this->currentPosition.y) / 10.f);
	}
}

Man::Man(sf::Vector2f currentPosition)
{
	this->currentPosition = sf::Vector2f(currentPosition);
	ManAi* manAi1 = new ManAi();
	this->manAi = manAi1;
}
Man::Man()
{
	ManAi* manAi1 = new ManAi();
	this->manAi = manAi1;
}

Man::~Man()
{
}
