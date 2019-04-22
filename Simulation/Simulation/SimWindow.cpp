#include "pch.h"
#include "SimWindow.h"

SimWindow::SimWindow()
{
	this->windowSize.x = 1080;
	this->windowSize.y = 720;

	this->create(sf::VideoMode(this->windowSize.x, this->windowSize.y), "Simple Simulation");
}

SimWindow::~SimWindow()
{
	close();
}
