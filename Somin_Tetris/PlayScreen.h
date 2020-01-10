#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Tetromino.h"
#include "Game.h"

const sf::Vector2f GAME_POSITION{ 10, 10 };

class PlayScreen : public Screen
{
public:
	PlayScreen();

	virtual const GameScreen run(sf::RenderWindow &window);

	const GameScreen mainLoop(sf::RenderWindow &window);

private:
	GameScreen m_curScreen{ GameScreen::PLAY };

	Game m_game;
};

