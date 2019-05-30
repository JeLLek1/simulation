#include "pch.h"
#include <math.h>
#include "Man.h"




void Man::draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite)
{
	if (this->isCorrect(map, simView))
	{
		sprite->setTextureRect(sf::IntRect( 0, this->direction()*sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
		sprite->setPosition(Simulation::cartToIso(this->currentPosition, map->mapWidth()));
		window->draw(*sprite);
		//Pasek wykonywania zadania (wielkoœæ oparta o wielkoœæ tekstury cz³owieka)
		if (!this->going) {
			//Czarne t³o paska
			sf::RectangleShape rectangle(sf::Vector2f(sprite->partSize.x, 10));
			rectangle.setFillColor(sf::Color::Black);
			rectangle.setPosition(sf::Vector2f(sprite->getPosition().x - sprite->partSize.x * 0.5, sprite->getPosition().y - sprite->partSize.y));
			window->draw(rectangle);
			//Sam pasek ³adowania
			sf::RectangleShape rectangle1(sf::Vector2f(this->actualWait / Man::COOLDOWN * (sprite->partSize.x - 4), 6));
			rectangle1.setFillColor(sf::Color::Green);
			rectangle1.setPosition(sf::Vector2f(sprite->getPosition().x - sprite->partSize.x * 0.5 + 2, sprite->getPosition().y - sprite->partSize.y + 2));
			window->draw(rectangle1);
		}
	}
}

sf::Vector2f Man::getCurrentPosition()
{
	return this->currentPosition;
}

Task Man::update(float dt, Map* map)
{
	//Jeœli s¹ kolejne kroki, sprawdzaj kroki
	if (this->going) {
		if (this->destination == this->currentPosition)
		{
			this->destination = sf::Vector2f(this->manAi->getNextStep(sf::Vector2u(this->currentPosition)));
			if (this->destination == this->currentPosition)
			{
				this->going = false;
			}
		}
		else
		{
			if (this->destination.x > this->currentPosition.x)
				this->currentPosition.x += Man::SPEED;
			else if (this->destination.x < this->currentPosition.x)
				this->currentPosition.x -= Man::SPEED;
			else if (this->destination.y > this->currentPosition.y)
				this->currentPosition.y += Man::SPEED;
			else if (this->destination.y < this->currentPosition.y)
				this->currentPosition.y -= Man::SPEED;
		}
	}
	//Jeœli nie, sprawdŸ aktualne zadanie i wykonuj czynnoœæ z nim zwi¹zan¹
	else {
		switch (this->currentTask)
		{
		case Task::GETWOOD:
			if (this->actualWait + dt < Man::COOLDOWN)
			{
				this->actualWait += dt;
			}
			else
			{
				this->currentTask = Task::RETURNRESOURCE;
				this->setPath(ObjectType::WARECHOUSE, map);
				this->pocket=ResouceType::WOOD;
				this->actualWait = 0;
				this->going = true;
			}
			break;
		case Task::GETSTONE:
			if (this->actualWait + dt < Man::COOLDOWN)
			{
				this->actualWait += dt;
			}
			else 
			{
				this->currentTask = Task::RETURNRESOURCE;
				this->setPath(ObjectType::WARECHOUSE, map);
				this->pocket=ResouceType::STONE;
				this->actualWait = 0;
				this->going = true;
			}
			break;
		case Task::BUILDFIREPLACE:
			if (this->actualWait + dt < Man::COOLDOWN)
			{
				this->actualWait += dt;
			}
			else
			{
				this->currentTask = Task::NONE;
				this->actualWait = 0;
			}
			break;
		case Task::RETURNRESOURCE:
			if (this->actualWait + dt < Man::COOLDOWN)
			{
				this->actualWait += dt;
			}
			else
			{
				this->currentTask = Task::NONE;
				this->actualWait = 0;
			}
			break;
		default:
			break;
		}
	}
	return this->currentTask;
}

bool Man::setPath(ObjectType objectType, Map* map, sf::Vector2u end)
{
	if(end.x==0 && end.y == 0)
		this->manAi->dijkstraPath(objectType, map, sf::Vector2u(this->currentPosition), end, false);
	else
		this->manAi->dijkstraPath(objectType, map, sf::Vector2u(this->currentPosition), end, true);

	return false;
}

Task Man::returnTask()
{
	return this->currentTask;
}

void Man::setTask(Task task, Map* map)
{
	sf::Vector2u round;
	bool test = false;
	switch (task)
	{
	case Task::GETWOOD:
		this->setPath(ObjectType::WOOD, map);
		break;
	case Task::GETSTONE:
		this->setPath(ObjectType::STONE, map);
		break;
	case Task::BUILDFIREPLACE:
		do {
			test = false;
			round.x = (rand() % (map->mapWidth() - 2)) + 1;
			round.y = (rand() % (map->mapHeight() - 2)) + 1;
			
			sf::Vector2u helper[8] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1), sf::Vector2u(1,1), sf::Vector2u(1,-1), sf::Vector2u(-1,1), sf::Vector2u(-1,-1) };
			for (int i = 0; i < 8; i++) {
				if (map->returnTile(round + helper[i])->returnCollision()) {
					test = true;
				}
			}
		} while (map->returnTile(round)->returnCollision() || test);

		this->setPath(ObjectType::NONE, map, round);

		break;
	case Task::RETURNRESOURCE:
		this->setPath(ObjectType::FIREPLACE, map);
		break;
	default:
		break;
	}
	this->currentTask = task;
	this->going = true;
}

ResouceType Man::getPocket()
{
	ResouceType temp = this->pocket;
	this->pocket = ResouceType::NONE;
	return temp;
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
	this->destination= sf::Vector2f(this->manAi->getNextStep(sf::Vector2u(this->currentPosition)));
	this->currentTask = Task::NONE;
	this->going = false;
	this->actualWait = 0.f;
	this->pocket = ResouceType::NONE;
}
Man::Man()
{
	this->currentPosition = sf::Vector2f(1,1);
	ManAi* manAi1 = new ManAi();
	this->manAi = manAi1;
	this->hp = 0;
	this->currentTask = Task::NONE;
	this->going = false;
	this->actualWait = 0.f;
	this->pocket = ResouceType::NONE;
}

Man::~Man()
{
}
