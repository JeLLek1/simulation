#include "pch.h"
#include "ManAi.h"


sf::Vector2i ManAi::getNextStep()
{
	if (!this->destination.empty())
	{
		sf::Vector2i temp = this->destination.front();
		this->destination.pop_front();
		return temp;
	}
	else return sf::Vector2i(1, 1);
}

ManAi::ManAi()
{
	this->destination.push_front(sf::Vector2i(50, 50));
	this->destination.push_front(sf::Vector2i(50, 49));
	this->destination.push_front(sf::Vector2i(50, 48));
}


ManAi::~ManAi()
{
}
