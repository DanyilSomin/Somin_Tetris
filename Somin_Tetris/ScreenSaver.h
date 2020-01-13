#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <memory>
#include <random>

#include "Tetromino.h"
#include "Settings.h"
#include "Screen.h"

constexpr int ROTATE_CHANCE{ 250 };
constexpr float SCREENSAWER_CELL_WIDTH{ 10 };
constexpr float SPASE_BETWEEN_TETROMINOS{ 60 };
constexpr float SPEED_DIVIDER{ 1 };

class ScreenSaver
{
public:
	ScreenSaver();

	void draw(sf::RenderWindow &window);

	void updateSpeed() { m_deltaTime = LEVEL_PERIODS[Settings::getPlayDifficulty().first] / SPEED_DIVIDER; }

private:
	sf::Clock m_clock;

	int m_deltaTime;

	std::list<std::unique_ptr<Tetromino>> m_tetrominos;

	void update();

	void initTetrominos();
};

