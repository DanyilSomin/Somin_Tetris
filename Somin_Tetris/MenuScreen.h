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
#include "ScreenSaver.h"
#include "MusicManager.h"

const sf::Vector2f MENU_FRAME_POSITION{ WINDOW_WIDTH / 2,  180 };
const sf::Vector2f STATS_FRAME_POSITION{ WINDOW_WIDTH / 2,  185 };

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual const GameScreen run(sf::RenderWindow &window);
	
	void startGame() { m_curScreen = GameScreen::PLAY; }

	void updateMusicMode();

private:
	GameScreen m_curScreen{ GameScreen::MENU };

	std::unique_ptr<PopoutFrame> m_popoutFrame;

	std::unique_ptr<ScreenSaver> m_screenSaver;

	void makePopoutMenu();

	void makePopoutStats();
};

