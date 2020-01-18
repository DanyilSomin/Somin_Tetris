#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Screens.h"
#include "Tetromino.h"
#include "Game.h"
#include "Button.h"
#include "PopoutFrame.h"
#include "MusicManager.h"

const sf::Vector2f GAME_POSITION{ 10, 10 };
const sf::Vector2f PAUSE_BTN_POSITION{ WINDOW_WIDTH - 71, WINDOW_HEIGHT - 55 };
const sf::Vector2f PAUSE_FRAME_POSITION{ (WINDOW_WIDTH / 2), 170 };

enum TextType { SCORE, LEVEL, LINE, TIME_WITHOUT_I, TETRIS_RATE, COUNT };

const std::array<sf::Vector2f, TextType::COUNT> TEXTS_POSITIONS
{
	sf::Vector2f{ 380, 135 }, 
	sf::Vector2f{ 380, 180 },
	sf::Vector2f{ 380, 225 },
	sf::Vector2f{ 380, 270 },
	sf::Vector2f{ 380, 315 }, 
};

class PlayScreen : public Screen
{
public:
	PlayScreen();

	virtual const GameScreen run(sf::RenderWindow &window);

	const GameScreen mainLoop(sf::RenderWindow &window);

	void goToMenu();

private:
	int m_charSize{ 24 };

	sf::Font m_font;

	GameScreen m_curScreen{ GameScreen::PLAY };

	void handleEvents(sf::RenderWindow &window);
	
	std::unique_ptr<PopoutFrame> m_pauseFrame;

	std::unique_ptr<PopoutFrame> m_gameOverFrame;
	
	std::unique_ptr<Game> m_game;

	std::unique_ptr<Button> m_pauseBtn;

	std::vector<std::unique_ptr<sf::Text>> m_texts;

	void updateText();
	void makePouseFrame();
};

