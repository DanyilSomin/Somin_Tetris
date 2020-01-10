#pragma once
#include <array>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"
#include "Settings.h"

constexpr int FIELD_WIDTH{ 10 }; // cells
constexpr int FIELD_HEIGHT{ 20 }; // cells

const std::string FIELD_IMG_PATH{ "Img\\field.png" };
const float CELL_WIDTH{ 34 };

const sf::Vector2f BORDER_WIDTH{ 3, 3 }; // px

const sf::Vector2i NEXT_TETROMINO_POS{ 1, 11 }; // cells
const sf::Vector2i INIT_TETROMINO_POS{ 0, 4 }; // cells

const sf::Vector2i DOWN { 1, 0 };
const sf::Vector2i UP   {-1, 0 };
const sf::Vector2i RIGHT{ 0, 1 };
const sf::Vector2i LEFT { 0,-1 };

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

	void gameOver() { m_gameOver = false; }
	
private:
	int m_score = 0;
	int m_line = 0;
	int m_timeWithoutI = 0;
	float m_tetrisRate = 0;

	int m_nextDownTime;

	bool m_gameOver = false;

	const sf::Vector2f m_position;

	sf::Clock m_clock;

	std::unique_ptr<Tetromino> m_curTetromino;
	std::unique_ptr<Tetromino> m_nextTetromino;

	sf::Vector2i m_curTetrominoPos;

	std::unique_ptr<sf::Texture> m_fieldTexture;
	std::unique_ptr<sf::Sprite> m_fieldSprite;
	
	std::vector<std::unique_ptr<sf::Texture>> m_blocksTextures;
	std::vector<std::unique_ptr<sf::Sprite>> m_blocksSprites;

	std::vector<std::array<TetrominoType, FIELD_WIDTH>> m_lines;

	void fixCurrentTetromino();

	bool checkPlace(const TState &state, const sf::Vector2i &delta = { 0, 0 }) const;

	const sf::Vector2f cellCoordinate(const sf::Vector2i &cell);

	int checkLines();
};

