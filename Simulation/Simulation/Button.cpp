#include "pch.h"
#include "Button.h"
#include <iostream>
#include"Simulation.h"




bool Button::coverage(sf::Vector2i mousePosition)
{
	if (mousePosition.y <= (this->text.getPosition().y + this->text.getLocalBounds().height) && mousePosition.y >= this->text.getPosition().y &&
		mousePosition.x <= (this->text.getPosition().x + this->text.getLocalBounds().width ) && mousePosition.x >= this->text.getPosition().x )
	{
		this->text.setFillColor(sf::Color::Black);
		return true;
	}
	else
	{
		this->text.setFillColor(sf::Color::White);
		return false;
	}
}

void Button::update(const float dt, Simulation* simulation)
{
	if(this->coverage(sf::Mouse::getPosition(*simulation->window)))
	{
		if (this->currentSize < Button::MAX_SIZE)
		{
			this->currentSize += dt * Button::SPEED;
			this->text.setCharacterSize(this->currentSize);
		}
			
	}
	else
	{
		if (this->currentSize > this->choosenSize)
		{
			this->currentSize -= dt * Button::SPEED;
			this->text.setCharacterSize(this->currentSize);
		}
	}
}



void Button::draw(sf::RenderWindow* window)
{
	window->draw(this->text);
}

Button::Button(const std::string& name, sf::Font* font, unsigned int fontSize)
{
	this->currentSize = this->choosenSize = fontSize;

	text.setCharacterSize(fontSize);

	this->size.x = this->text.getLocalBounds().width;
	this->size.y = this->text.getLocalBounds().height;
	this->text.setOrigin(size * 0.5f);

	sf::Vector2f position;

	this->text.setString(name);
	this->text.setFont(*font);

	position.x = Button::DISTANCE + this->size.x / 2;
	position.y = Button::DISTANCE + this->size.y / 2;

	this->text.setPosition(position);

}

Button::Button(const std::string& name, sf::Font* font, Button* button, unsigned int fontSize)
{
	this->currentSize = this->choosenSize = fontSize;

	text.setCharacterSize(fontSize);

	this->size.x = this->text.getLocalBounds().width;
	this->size.y = this->text.getLocalBounds().height;
	this->text.setOrigin(size * 0.5f);

	sf::Vector2f position;

	this->text.setString(name);
	this->text.setFont(*font);
	position.x = Button::DISTANCE + this->size.x / 2;

	if (button == NULL) position.y = Button::DISTANCE + this->size.y / 2;
	else
	{
		position.y = button->text.getPosition().y + Button::DISTANCE + button->size.y / 2 + this->size.y / 2;
	}

	this->text.setPosition(position);
}



Button::~Button()
{
}
