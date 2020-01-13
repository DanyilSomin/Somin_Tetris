#pragma once
#include <array>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"
#include "Settings.h"

constexpr int FIELD_WIDTH{ 10 }; // cells
constexpr int FIELD_HEIGHT{ 20 }; // cells
constexpr int TETRIS{ 4 };
constexpr float CELL_WIDTH{ 34 }; // px

const std::string FIELD_IMG_PATH{ "Img\\Field.png" };
const std::string NEXT_TETROMINO_BACKGROUND_IMG_PATH{ "Img\\NextTetrominoBackground.png" };

const sf::Vector2f BORDER_WIDTH{ 3, 3 }; // px
const sf::Vector2f FIELD_POSITION{ 0, 0 }; // px
const sf::Vector2f NEXT_TETROMINO_BACKGROUND_POSITION{ 368, 0 }; // px
const sf::Vector2f NEXT_TETROMINO_PX_POS
	{ NEXT_TETROMINO_BACKGROUND_POSITION + sf::Vector2f{ 3, 3 } }; // px

const sf::Vector2i INIT_TETROMINO_POS{ 0, 4 }; // cells
const sf::Vector2i DOWN { 1, 0 }; // cells
const sf::Vector2i UP   {-1, 0 }; // cells
const sf::Vector2i RIGHT{ 0, 1 }; // cells
const sf::Vector2i LEFT { 0,-1 }; // cells

const std::array<int, 5> SCORE_POINTS_COEF{ 0, 40, 100, 300, 1200 }; // score points
const std::array<int, 30> LEVEL_PERIODS{ 1660, 1570, 1480, 1390, 1300, 1210, 1120, 1030, 940,  850,
										 810,  790,  750,  690,  630,  570,  510,  450,  400,  390, 
										 340,  300,  780,  250,  220,  190,  160,  130,  100,  80  }; // ms

struct GameStats
{
	int score = 0;
	int line = 0;
	int level = 0;
	int timeWithoutI = 0;
	int tetrisLinesAmount = 0;
};

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

	void gameOver() { saveStats(); m_isGameOver = true; }
	
	void restart();
	void pause_start();
	bool isPaused() const { return m_isPaused; }
	bool isGameOver() const { return m_isGameOver; }

	const GameStats &getStats() const { return m_stats; }
	
private:
	GameStats m_stats;

	bool m_isPaused{ false };

	int m_linesBeforeNextLevel{ 0 };

	int m_nextDownTime{ 0 };

	const int m_startLevel{ 0 };

	bool m_isGameOver = { false };

	const sf::Vector2f m_position;

	sf::Clock m_clock;

	std::unique_ptr<Tetromino> m_curTetromino;
	std::unique_ptr<Tetromino> m_nextTetromino;

	sf::Vector2i m_curTetrominoPos;

	std::vector<std::unique_ptr<sf::Texture>> m_textures;
	std::vector<std::unique_ptr<sf::Sprite>> m_sprites;
	
	std::vector<std::unique_ptr<sf::Texture>> m_blocksTextures;
	std::vector<std::unique_ptr<sf::Sprite>> m_blocksSprites;

	std::vector<std::array<TetrominoType, FIELD_WIDTH>> m_lines;

	void fixCurrentTetromino();

	bool checkPlace(const TState &state, const sf::Vector2i &delta = { 0, 0 }) const;

	const sf::Vector2i findRotationShift();

	const sf::Vector2f cellCoordinate(const sf::Vector2i &cell);

	int checkLines();

	void saveStats() {}
};

