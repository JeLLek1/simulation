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
	this->simulation->getWindow()->setView(this->view);
	this->simulation->getWindow()->clear(sf::Color::Black);
	this->simulation->getWindow()->draw(this->simulation->getBackground());
	for (auto const& i : buttons) 
	{
		i->draw(simulation->getWindow());
	}
	return;
}

void SimulationStateStart::update(const float dt)
{
	for (auto const& i : buttons)
	{
		i->update(dt, simulation);
	}
	
	simulation->getSprDivMgr()->update(dt);
	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

bool SimulationStateStart::handleInput()
{
	sf::Event event;

	while (this->simulation->getWindow()->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
			{
				simulation->getWindow()->close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					return false;
				else if (event.key.code == sf::Keyboard::Space)
					this->loadSimulation();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left){
					ButtonEvents buttonEvent=ButtonEvents::DO_NOTHING;
					for (auto const& button : buttons) {
						if (button->coverage(sf::Mouse::getPosition(*this->simulation->getWindow()))) {
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
						this->simulation->getWindow()->close();
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

	return true;
}

SimulationStateStart::SimulationStateStart(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->getWindow()->getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	buttons.push_back(new Button("START", simulation->getFont(), ButtonEvents::SIMULATION_START , 40));
	buttons.push_back(new Button("EDITOR", simulation->getFont(), buttons.back(), ButtonEvents::MAP_EDITOR, 40));
	buttons.push_back(new Button("EXIT", simulation->getFont(), buttons.back(), ButtonEvents::WINDOW_CLOSE, 40));
}


SimulationStateStart::~SimulationStateStart()
{
	//Usuwanie wszystkich elementów listy z wywo³aniem ich destruktorów
	this->buttons.remove_if([](Button * theElement) {delete theElement; return true; });
}
