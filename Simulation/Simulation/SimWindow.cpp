#include "pch.h"
#include "SimWindow.h"

SimWindow::SimWindow()
{
	this->windowSize.x = 1920;
	this->windowSize.y = 1080;

	this->create(sf::VideoMode(this->windowSize.x, this->windowSize.y), "Simple Simulation"/*, sf::Style::Fullscreen*/);
}

SimWindow::~SimWindow()
{
	close();
}
