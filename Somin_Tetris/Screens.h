#pragma once

#include <SFML/Graphics.hpp>

enum GameScreen
{
	MENU,
	PLAY,
	EXIT,
};

constexpr int WINDOW_WIDTH = 624;
constexpr int WINDOW_HEIGHT = 724;
constexpr int FRAMERATE = 60;
const sf::Color WINDOW_BACKGROUND{ 60, 54, 54, 255 };

#include "Screen.h"
#include "MenuScreen.h"
#include "PlayScreen.h"



