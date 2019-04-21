#include "pch.h"
#include "SimWindow.h"


void SimWindow::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings settings)
{
	this->windowSize.x = mode.width;
	this->windowSize.y = mode.height;
	this->windowName = title;
	sf::RenderWindow::create(mode, title, style, settings);
}

SimWindow::SimWindow() : sf::RenderWindow()
{
}

SimWindow::~SimWindow()
{
	close();
}
