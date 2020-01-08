#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Button.h"

#include "Timer.h"

constexpr int PLAY_BTN_HEIGHT = 200;
constexpr int MODE_BTN_HEIGHT = 250;

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual GameScreen run(sf::RenderWindow &window);

private:
	GameScreen m_curScreen{ GameScreen::MENU };

	std::vector<std::unique_ptr<Button>> m_buttons;

	void startGame() { m_curScreen = GameScreen::GAME; }
};

