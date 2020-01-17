#pragma once
#include <array>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"
#include "Settings.h"
#include "Field.h"
#include "GameStats.h"
#include "MusicManager.h"

constexpr float CELL_WIDTH{ 34 }; // px

const std::string NEXT_TETROMINO_BACKGROUND_IMG_PATH{ "Img\\NextTetrominoBackground.png" };

const sf::Vector2f FIELD_POSITION{ 0, 0 }; // px
const sf::Vector2f NEXT_TETROMINO_BACKGROUND_POSITION{ 368, 0 }; // px
const sf::Vector2f NEXT_TETROMINO_PX_POS
	{ NEXT_TETROMINO_BACKGROUND_POSITION + sf::Vector2f{ 3, 3 } }; // px

const sf::Vector2i INIT_TETROMINO_POS{ 4, 0 }; // cells
const sf::Vector2i DOWN { 0, 1 }; // cells
const sf::Vector2i UP   { 0,-1 }; // cells
const sf::Vector2i RIGHT{ 1, 0 }; // cells
const sf::Vector2i LEFT {-1, 0 }; // cells
const sf::Vector2i FIELD_SIZE{ 10, 20 }; // cells

class Game
{
public:
	Game(const sf::Vector2f &position);

	void update();

	void up();
	void left();
	void right();
	void down();

	void draw(sf::RenderWindow &window);

	void gameOver();
	
	void restart();
	void pause_start();
	bool isPaused() const { return m_isPaused; }
	bool isGameOver() const { return m_isGameOver; }

	const GameStats &getStats() const { return m_stats; }
	
private:
	GameStats m_stats;

	bool m_isPaused{ false };

	bool m_isGameOver{ false };

	const sf::Vector2f m_position;

	sf::Clock m_clock;

	std::unique_ptr<Tetromino> m_curTetromino;
	std::unique_ptr<Tetromino> m_nextTetromino;

	std::vector<std::unique_ptr<sf::Texture>> m_textures;
	std::vector<std::unique_ptr<sf::Sprite>> m_sprites;

	sf::Vector2i m_curTetrominoPos;

	Field m_field;
};

