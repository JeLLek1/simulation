#include "pch.h"
#include <string>
#include "PeopleMenager.h"
#include <conio.h>
#include <iostream>


void PeopleMenager::drawGUI(sf::View* guiView, sf::RenderWindow* window, SpriteDividedMenager* spriteMgr, sf::Font* font)
{
	sf::RectangleShape rectangle1(sf::Vector2f(guiView->getSize().x, 30));
	rectangle1.setFillColor(sf::Color(100, 150, 150));
	rectangle1.setPosition(sf::Vector2f(0,guiView->getSize().y-rectangle1.getSize().y));
	window->draw(rectangle1);
	
	
	sf::Text text;
	sf::Sprite sprite;
	sprite = *spriteMgr->getRef(TextureNames::ICON);
	sf::Vector2f textPos = (sf::Vector2f(50, guiView->getSize().y - (text.getCharacterSize() + (30 - text.getCharacterSize()) / 2)));
	sf::Vector2f spritePos = sf::Vector2f(textPos.x, textPos.y+25);

	sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
	text.setFont(*font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(textPos);
	sprite.setPosition(spritePos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::STONE)));
	window->draw(text);
	window->draw(sprite);
	textPos.x += guiView->getSize().x / 4;
	text.setPosition(textPos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::WOOD)));
	sprite.setTextureRect(sf::IntRect(20, 0, 20, 20));
	spritePos = sf::Vector2f(textPos.x, textPos.y + 25);
	sprite.setPosition(spritePos);
	window->draw(sprite);
	window->draw(text);
	textPos.x += guiView->getSize().x / 4;
	text.setPosition(textPos);
	text.setString(std::to_string(this->ownedResouces.at(ResouceType::STRAWBERRY)));
	sprite.setTextureRect(sf::IntRect(40, 0, 20, 20));
	spritePos = sf::Vector2f(textPos.x, textPos.y + 25);
	sprite.setPosition(spritePos);
	window->draw(sprite);
	window->draw(text);
	textPos.x += guiView->getSize().x / 4;
	text.setPosition(textPos);
	text.setString(std::to_string(this->population.size())+" / 20");
	sprite.setTextureRect(sf::IntRect(60, 0, 20, 20));
	spritePos = sf::Vector2f(textPos.x, textPos.y + 25);
	sprite.setPosition(spritePos);
	window->draw(sprite);
	window->draw(text);
}

void PeopleMenager::draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDividedMenager* spriteMgr)
{
	for (auto const& i : this->population)
	{
		i->draw((simView), window, map, spriteMgr->getRef(TextureNames::MAN));
	}
	for (auto const& i : this->staticObjects)
	{
		i->draw(window, spriteMgr->getRef(TextureNames::SOURCES), map->mapWidth(), spriteMgr->returnAnimationStep());
	}
}

bool PeopleMenager::update(float dt, Map* map)
{
	for (auto const& i : population)
	{

		if (i->update(dt, map) == Task::NONE)
		{
			ResouceType temp1 = i->getPocket();
			if (this->ownedResouces.at(ResouceType::STONE) >= 2 && this->ownedResouces.at(ResouceType::WOOD) >= 2 && this->ownedResouces.at(ResouceType::STRAWBERRY) >= 2) {

				this->ownedResouces.at(ResouceType::STONE) -= 2;
				this->ownedResouces.at(ResouceType::WOOD) -= 2;
				this->ownedResouces.at(ResouceType::STRAWBERRY) -= 2;
				i->setTask(Task::BUILDFIREPLACE, map);
			}else{
				Task temp;

				if (temp1 != ResouceType::NONE)
				{
					this->ownedResouces.at(temp1)++;
				}
				else {
					StaticObject *fireplace = new StaticObjectFireplace(ObjectType::FIREPLACE, &sf::Vector2u(i->getCurrentPosition()));
					this->staticObjects.push_front(fireplace);

					//Do wylosowania pozycji pierwszego hopka w okó³ ogniska
					sf::Vector2u helper[8] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1), sf::Vector2u(1,1), sf::Vector2u(1,-1), sf::Vector2u(-1,1), sf::Vector2u(-1,-1) };
					//Tworzenie cz³owieka
					Man * man = new Man(sf::Vector2f(fireplace->getPosition() + helper[rand() % 8]));
					this->population.push_front(man);
					man->setTask(Task::GETWOOD, map);
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
					temp = Task::GETFOOD;
				}

				i->setTask(temp, map);
			}
		}
	}

	if (this->population.size() > 0) {
		return false;
	}
	return true;
}

PeopleMenager::PeopleMenager(Map* map, sf::Vector2u* warehousePos, sf::Vector2u* fireplacePos)
{
	//Do wylosowania pozycji pierwszego hopka w okó³ ogniska
	sf::Vector2u helper[8] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1), sf::Vector2u(1,1), sf::Vector2u(1,-1), sf::Vector2u(-1,1), sf::Vector2u(-1,-1)};
	//Tworzenie drzew
	for (int i = 0; i < 3; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::WOOD, map);
		this->staticObjects.push_front(object);
	}
	//Tworzenie drzew
	for (int i = 0; i < 3; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::STRAWBERRY, map);
		this->staticObjects.push_front(object);
	}
	//Tworzenie kamenia
	for (int i = 0; i < 3; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::STONE, map);
		this->staticObjects.push_front(object);
	}
	//Pozycje ogniska i warehouse pobrane z pliku binarnego
	StaticObject *fireplace = new StaticObjectFireplace(ObjectType::FIREPLACE, fireplacePos);
	this->staticObjects.push_front(new StaticObjectResouces(ObjectType::WARECHOUSE, warehousePos));
	this->staticObjects.push_front(fireplace);

	//Dodawanie listy surowców z ich wartoœciami
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::STONE, 0));
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::WOOD, 0));
	this->ownedResouces.insert(std::pair<ResouceType, int>(ResouceType::STRAWBERRY, 0));

	//Tworzenie cz³owieka
	Man* man = new Man(sf::Vector2f(fireplace->getPosition()+helper[rand()%8]));
	this->population.push_front(man);
	man->setTask(Task::GETWOOD, map);
}


PeopleMenager::~PeopleMenager()
{

	this->population.remove_if([](Man * theElement) {delete theElement; return true; });
}
