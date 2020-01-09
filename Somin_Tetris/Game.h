#pragma once
#include <array>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"

constexpr int FIELD_WIDTH{ 10 };
constexpr int FIELD_HEIGHT{ 10 };


class Game
{
public:
	void update();
	void up();
	void left();
	void right();

	void draw();
	
private:
	int m_score = 0;
	int m_line = 0;
	int m_timeWithoutI = 0;

	float m_tetrisRate = 0;

	sf::Clock m_clock;

	std::unique_ptr<Tetromino> m_curTetromino;
	std::unique_ptr<Tetromino> m_nextTetromino;

	std::unique_ptr<sf::Texture> m_fieldTexture;
	std::unique_ptr<sf::Sprite> m_fieldSprite;
	
	std::vector<std::unique_ptr<sf::Texture>> m_blocksTextures;
	std::vector<std::unique_ptr<sf::Sprite>> m_blocksSprites;

	std::vector<std::array<TetrominoType, FIELD_WIDTH>> m_lines;

	void fixCurrentTetromino();

	bool checkPlace(const TState &state, sf::Vector2i delta) const;

	void checkLines();
};

