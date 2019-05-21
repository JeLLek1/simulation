#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "pch.h"
#include "SimulationState.h"
#include "SimulationStateStart.h"
#include "SimulationStateMain.h"
#include "SimulationStateEditor.h"

void SimulationStateStart::loadSimulation()
{
	this->simulation->pushState(new SimulationStateMain(this->simulation));

	return;
}
void SimulationStateStart::loadEditor() {
	this->simulation->pushState(new SimulationStateEditor(this->simulation));

	return;
}

void SimulationStateStart::draw(const float dt)
{
	this->simulation->window->setView(this->view);
	this->simulation->window->clear(sf::Color::Black);
	this->simulation->window->draw(this->simulation->background);
	for (auto const& i : buttons) 
	{
		i->draw(simulation->window);
	}
	return;
}

void SimulationStateStart::update(const float dt)
{
	for (auto const& i : buttons)
	{
		i->update(dt, simulation);
	}
	simulation->sprDivMgr.update(dt);
	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateStart::handleInput()
{
	sf::Event event;

	while (this->simulation->window->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
			{
				simulation->window->close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->window->close();
				else if (event.key.code == sf::Keyboard::Space)
					this->loadSimulation();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left){
					ButtonEvents buttonEvent=ButtonEvents::DO_NOTHING;
					for (auto const& button : buttons) {
						if (button->coverage(sf::Mouse::getPosition(*this->simulation->window))) {
							buttonEvent = button->getEvent();
						}
					}
					switch (buttonEvent) {
					case ButtonEvents::SIMULATION_START:
						this->loadSimulation();
						break;
					case ButtonEvents::MAP_EDITOR:
						this->loadEditor();
						break;
					case ButtonEvents::WINDOW_CLOSE:
						this->simulation->window->close();
						break;
					default:
						break;
					}
				}
			}
			default: 
				break;
		}
	}

	return;
}

SimulationStateStart::SimulationStateStart(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window->getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	buttons.push_back(new Button("START", simulation->font, ButtonEvents::SIMULATION_START , 40));
	buttons.push_back(new Button("EDITOR", simulation->font, buttons.back(), ButtonEvents::MAP_EDITOR, 40));
	buttons.push_back(new Button("EXIT", simulation->font, buttons.back(), ButtonEvents::WINDOW_CLOSE, 40));
}


SimulationStateStart::~SimulationStateStart()
{
	//Usuwanie wszystkich elementów listy z wywo³aniem ich destruktorów
	buttons.remove_if([](Button * theElement) {delete theElement; return true; });
}
