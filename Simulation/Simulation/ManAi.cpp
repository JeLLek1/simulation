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
	this->destination.push_front(sf::Vector2i(5, 50));
	this->destination.push_front(sf::Vector2i(30, 49));
	this->destination.push_front(sf::Vector2i(40, 4));
	this->destination.push_front(sf::Vector2i(30, 48));
	this->destination.push_front(sf::Vector2i(20, 28));
	this->destination.push_front(sf::Vector2i(10, 2));
	this->destination.push_front(sf::Vector2i(30, 48));
	this->destination.push_front(sf::Vector2i(50, 18));
	this->destination.push_front(sf::Vector2i(20, 48));
	this->destination.push_front(sf::Vector2i(50, 8));
}


ManAi::~ManAi()
{
}
