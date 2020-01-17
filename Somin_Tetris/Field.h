#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"

const sf::Vector2f BORDER_WIDTH{ 3, 3 }; // px

const std::string FIELD_IMG_PATH{ "Img\\Field.png" };

class Field
{
public:
	Field(const sf::Vector2f &position, const sf::Vector2i &size, int cellWidth);

	void draw(sf::RenderWindow &window);

	bool fixTetromino(const Tetromino &state, const sf::Vector2i &position);

	bool checkPlace(const TState &state, const sf::Vector2i &position = { 0, 0 }) const;

	const sf::Vector2i findRotationShift(const TState &state, const sf::Vector2i &position);

	const sf::Vector2f cellCoordinate(const sf::Vector2i &cell);

	void clear() { m_lines.clear(); }

	int checkLines();

private:
	const sf::Vector2i m_size;
	const int m_cellWidth;

	const sf::Vector2f m_position;

	std::unique_ptr<sf::Texture> m_fieldTexture;
	std::unique_ptr<sf::Sprite> m_fieldSprite;

	std::vector<std::unique_ptr<sf::Texture>> m_blocksTextures;
	std::vector<std::unique_ptr<sf::Sprite>> m_blocksSprites;

	std::vector<std::vector<TetrominoType>> m_lines;
};

