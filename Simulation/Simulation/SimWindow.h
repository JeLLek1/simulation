#pragma once

#include<SFML/Graphics.hpp>
#include<string>
#include <SFML/System/String.hpp>

class SimWindow : public sf::RenderWindow
{
private:

	sf::Vector2i windowSize;
	sf::String windowName;

public:
	

	SimWindow();
	~SimWindow();
};

