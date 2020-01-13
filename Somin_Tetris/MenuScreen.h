#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Button.h"
#include "PopoutFrame.h"
#include "ScreenSaver.h"

const sf::Vector2f MENU_FRAME_POSITION{ WINDOW_WIDTH / 2,  180 };

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual const GameScreen run(sf::RenderWindow &window);
	
	void startGame() { m_curScreen = GameScreen::PLAY; }

	void updateMusicMode();

private:
	sf::Music m_music;

	GameScreen m_curScreen{ GameScreen::MENU };

	std::unique_ptr<PopoutFrame> m_popoutFrame;

	std::unique_ptr<ScreenSaver> m_screenSaver;
};

