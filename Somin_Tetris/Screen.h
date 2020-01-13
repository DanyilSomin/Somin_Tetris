#pragma once
#include <SFML/Graphics.hpp>

enum GameScreen;

class Screen
{
public:
	virtual const GameScreen run(sf::RenderWindow &window) = 0;
};

constexpr int WINDOW_WIDTH = 571;
constexpr int WINDOW_HEIGHT = 724;
constexpr int FRAMERATE = 24;
const sf::Color WINDOW_BACKGROUND{ 60, 54, 54, 255 };

