#pragma once

#include<SFML/Graphics.hpp>
#include<string>
#include <SFML/System/String.hpp>

class SimWindow : public sf::RenderWindow
{
public:
	
	sf::Vector2i windowSize;
	sf::String windowName;

	SimWindow();
	~SimWindow();
};

