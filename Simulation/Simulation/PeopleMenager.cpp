#include "pch.h"
#include <string>
#include "PeopleMenager.h"


void PeopleMenager::drawGUI(sf::View* guiView, sf::RenderWindow* window, SpriteDividedMenager* spriteMgr, sf::Font* font)
{
	sf::RectangleShape rectangle1(sf::Vector2f(guiView->getSize().x, 30));
	rectangle1.setFillColor(sf::Color::Magenta);
	rectangle1.setPosition(sf::Vector2f(0,guiView->getSize().y-rectangle1.getSize().y));
	window->draw(rectangle1);
	
	
	sf::Text text;
	sf::Vector2f textPos = (sf::Vector2f(50, guiView->getSize().y - (text.getCharacterSize() + (30 - text.getCharacterSize()) / 2)));
	text.setFont(*font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(textPos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::STONE)));
	window->draw(text);
	textPos.x += guiView->getSize().x / 3;
	text.setPosition(textPos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::WOOD)));
	window->draw(text);
	textPos.x += guiView->getSize().x / 3;
	text.setPosition(textPos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::STRAWBERRY)));
	window->draw(text);
}

void PeopleMenager::draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDividedMenager* spriteMgr)
{
	this->population.front()->draw((simView), window, map, spriteMgr->getRef(TextureNames::MAN));

	for (auto const& i : staticObjects)
	{
		i->draw(window, spriteMgr->getRef(TextureNames::SOURCES), map->mapWidth(), spriteMgr->returnAnimationStep());
	}
}

void PeopleMenager::update(float dt, Map* map)
{
	for (auto const& i : population)
	{

		if (i->update(dt, map) == Task::NONE)
		{
			Task temp;

			ResouceType temp1 = i->getPocket();

			if (temp1 != ResouceType::NONE)
			{
				this->ownedResouces.at(temp1)++;
			}

			ResouceType min = ResouceType::WOOD;
			temp = Task::GETWOOD;

			if (this->ownedResouces.at(min) > this->ownedResouces.at(ResouceType::STONE))
			{
				min = ResouceType::STONE;
				temp = Task::GETSTONE;
			}
			if (this->ownedResouces.at(min) > this->ownedResouces.at(ResouceType::STRAWBERRY))
			{
				min = ResouceType::STRAWBERRY;
			}

			i->setTask(temp, map);
		}
	}
	for (auto const& i : staticObjects)
	{
		i->update(dt);
	}
}

PeopleMenager::PeopleMenager(Map* map, StaticObjectFireplace* fireplace, StaticObjectResouces* warehouse)
{
	//Do wylosowania pozycji pierwszego hopka w ok� ogniska
	sf::Vector2u helper[8] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1), sf::Vector2u(1,1), sf::Vector2u(1,-1), sf::Vector2u(-1,1), sf::Vector2u(-1,-1)};
	//Tworzenie drzew
	for (int i = 0; i < 3; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::WOOD, map);
		this->staticObjects.push_front(object);
	}
	//Tworzenie kamenia
	for (int i = 0; i < 3; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::STONE, map);
		this->staticObjects.push_front(object);
	}
	//Pozycje ogniska i warehouse pobrane z pliku binarnego
	this->staticObjects.push_front(fireplace);
	this->staticObjects.push_front(warehouse);

	//Dodawanie listy surowc�w z ich warto�ciami
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::STONE, 0));
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::WOOD, 0));
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::STRAWBERRY, 100));

	
	Man* man = new Man(sf::Vector2f(fireplace->getPosition()+helper[rand()%8]));
	this->population.push_front(man);
	man->setTask(Task::NONE, map);
	
}


PeopleMenager::~PeopleMenager()
{
}
