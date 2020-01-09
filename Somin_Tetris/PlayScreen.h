#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Tetromino.h"

const sf::Vector2f FIELD_POSITION{ 10, 10 };
const std::string FIELD_IMG_PATH{ "Img\\field.png" };
const int CELL_WIDTH{ 34 };

class PlayScreen : public Screen
{
public:
	PlayScreen();

	virtual const GameScreen run(sf::RenderWindow &window);

	const GameScreen mainLoop(sf::RenderWindow &window);

private:
	GameScreen m_curScreen{ GameScreen::PLAY };

};

