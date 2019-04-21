#pragma once

#include<SFML/Graphics.hpp>
#include<string>
#include "../../SFML-2.5.1/include/SFML/System/String.hpp"

class SimWindow : public sf::RenderWindow
{
public:
	
	sf::Vector2i windowSize;
	sf::String windowName;


	void create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings settings = sf::ContextSettings());

	SimWindow();
	~SimWindow();
};

