#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Button.h"
#include "PopoutFrame.h"

const sf::Vector2f MENU_FRAME_POSITION{ WINDOW_WIDTH / 2,  200 };

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual const GameScreen run(sf::RenderWindow &window);
	
	void startGame() { m_curScreen = GameScreen::PLAY; }

private:
	GameScreen m_curScreen{ GameScreen::MENU };

	std::unique_ptr<PopoutFrame> m_popoutFrame;
};

