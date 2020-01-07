#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Button.h"

//const std::map<std::string> diffLevels{ {"Casual", "Low"}, 
//										{"Low", "Normal"},
//										{"Normal", "Hard"} };
//const std::map<std::string> playModes{ "Single", "Two players", "With bot" };

constexpr int PLAY_BTN_HEIGHT = 200;

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual GameScreen run(sf::RenderWindow &window);

	void whatever() const;

private:
	GameScreen m_curScreen{ GameScreen::MENU };

	std::vector<std::unique_ptr<Button>> m_buttons;

	void startGame() { m_curScreen = GameScreen::GAME; }
};

