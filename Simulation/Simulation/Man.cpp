#include "pch.h"
#include "Man.h"




void Man::draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite, float dt)
{
	this->update(dt); //to do zmiany!!!! powinno by� w update metodzie a nie w draw
	if (this->isCorrect(map, simView))
	{
		sprite->setTextureRect(sf::IntRect( 0, this->direction()*sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
		sprite->setPosition(Simulation::cartToIso(this->currentPosition, map->mapWidth()));
		window->draw(*sprite);
	}
}

void Man::update(float dt)
{
	if (this->currentPosition == this->destination)
		this->destination = sf::Vector2f(this->manAi->getNextStep(sf::Vector2i(this->currentPosition)));
	else
	{ 
		if (this->destination.x > this->currentPosition.x)
			this->currentPosition.x+=0.25; 
		else if (this->destination.x < this->currentPosition.x)
			this->currentPosition.x-= 0.25;
		else if (this->destination.y > this->currentPosition.y)
			this->currentPosition.y += 0.25;
		else if (this->destination.y < this->currentPosition.y)
			this->currentPosition.y -= 0.25;
	}
}

bool Man::setPath(ObjectType objectType, Map* map)
{
	this->manAi->dijkstraPath(objectType, map, sf::Vector2u(this->currentPosition));
	return false;
}

unsigned int Man::direction()
{
	if (this->currentPosition.x <= this->destination.x && this->currentPosition.y <= this->destination.y) return 0; //prawy dol
	else if (this->currentPosition.x <= this->destination.x && this->currentPosition.y >= this->destination.y) return 1; //prawa gora
	else if (this->currentPosition.x >= this->destination.x && this->currentPosition.y >= this->destination.y) return 2; //lewa gora
	else if (this->currentPosition.x >= this->destination.x && this->currentPosition.y <= this->destination.y) return 3; //lewy dol
	else return 0;
}

bool Man::isCorrect(Map* map, SimView* view)
{
	if (this->currentPosition.x >= (view->getCamPos().x - map->mapHeight() / 2) &&
		this->currentPosition.x <= (view->getCamPos().x + map->mapHeight() / 2) &&
		this->currentPosition.y <= (view->getCamPos().y + map->mapWidth() / 2) &&
		this->currentPosition.y >= (view->getCamPos().y - map->mapWidth() / 2))
		return true;
	else return false;
}

Man::Man(sf::Vector2f currentPosition)
{
	this->currentPosition = sf::Vector2f(currentPosition);
	ManAi* manAi1 = new ManAi();
	this->manAi = manAi1;
	this->hp = 0;
	this->destination= sf::Vector2f(this->manAi->getNextStep(sf::Vector2i(this->currentPosition)));
}
Man::Man()
{
	this->currentPosition = sf::Vector2f(1,1);
	ManAi* manAi1 = new ManAi();
	this->manAi = manAi1;
	this->hp = 0;
}

Man::~Man()
{
}
