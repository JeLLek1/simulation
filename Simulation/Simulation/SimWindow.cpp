#include "pch.h"
#include "SimWindow.h"

SimWindow::SimWindow() : sf::RenderWindow(sf::VideoMode(1920, 1080), "Simple Simulation")
{
	this->windowSize.x = 1920;
	this->windowSize.y = 1080;
}

SimWindow::~SimWindow()
{
	close();
}
