#pragma once
#include <SFML/Graphics.hpp>

enum GameScreen;

class Screen
{
public:
	
	virtual const GameScreen run(sf::RenderWindow &window) = 0;
};

