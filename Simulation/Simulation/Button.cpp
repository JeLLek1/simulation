#include "pch.h"
#include "Button.h"
#include"Simulation.h"




bool Button::coverage(sf::Vector2i mousePosition)
{

	if (mousePosition.y <= (this->text.getPosition().y + this->text.getCharacterSize()) && mousePosition.y >= this->text.getPosition().y &&
		mousePosition.x <= (this->text.getPosition().x + this->text.getLocalBounds().width ) && mousePosition.x >= this->text.getPosition().x )
	{
		return true;
	}

	return false;
}

void Button::update(const float dt, Simulation* simulation)
{
	if(this->coverage(sf::Mouse::getPosition(*simulation->getWindow())))
	{
		this->text.setFillColor(sf::Color::Black);
		if (this->currentSize < Button::MAX_SIZE)
		{
			this->currentSize += dt * Button::SPEED;
			this->text.setCharacterSize(this->currentSize);
			this->text.setPosition(this->text.getPosition().x - (dt * Button::SPEED) / 2, this->text.getPosition().y - (dt * Button::SPEED) / 2);
		}
			
	}
	else
	{
		this->text.setFillColor(sf::Color::White);
		if (this->currentSize > this->choosenSize)
		{
			this->currentSize -= dt * Button::SPEED;
			this->text.setCharacterSize(this->currentSize);
			this->text.setPosition(this->text.getPosition().x + (dt * Button::SPEED), this->text.getPosition().y + (dt * Button::SPEED));
		}
	}
}



void Button::draw(sf::RenderWindow* window)
{
	window->draw(this->text);
}

ButtonEvents Button::getEvent()
{
	return this->buttonEvent;
}

Button::Button(const std::string& name, sf::Font* font, ButtonEvents buttonEvent, unsigned int fontSize)
{
	this->buttonEvent = buttonEvent;
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

Button::Button(const std::string& name, sf::Font* font, Button* button, ButtonEvents buttonEvent, unsigned int fontSize)
{
	this->buttonEvent = buttonEvent;
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
