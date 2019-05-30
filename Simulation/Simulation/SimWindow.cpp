#include "pch.h"
#include "SimWindow.h"

SimWindow::SimWindow()
{
	//Ustalanie wielkoœci okna
	this->windowSize.x = 1080;
	this->windowSize.y = 720;
	//Tworzenie okna
	this->create(sf::VideoMode(this->windowSize.x, this->windowSize.y), "Simple Simulation"/*, sf::Style::Fullscreen*/);
}

SimWindow::~SimWindow()
{
	close();
}
