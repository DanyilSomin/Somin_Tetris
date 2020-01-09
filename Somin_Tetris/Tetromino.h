#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <random> 

#include "TetrominosStates.h"

enum TetrominoType { O, J, L, T, S, Z, I, TETROMINO_TYPES_COUNT, RANDOM, NONE, };

const std::string O_IMG_PATH{ "Img\\O.png" };
const std::string J_IMG_PATH{ "Img\\J.png" };
const std::string L_IMG_PATH{ "Img\\L.png" };
const std::string T_IMG_PATH{ "Img\\T.png" };
const std::string S_IMG_PATH{ "Img\\S.png" };
const std::string Z_IMG_PATH{ "Img\\Z.png" };
const std::string I_IMG_PATH{ "Img\\I.png" };

class Tetromino
{
public:
	Tetromino(const sf::Vector2f &position, float cellWidth, TetrominoType type = RANDOM);

	void draw(sf::RenderWindow &window);

	void move(const sf::Vector2f &delta) { m_position += delta; }

	void setPosition(const sf::Vector2f &pos) { m_position = pos; }

	void rotate();

	const TState &curState() const { return *m_curState; }

private:
	const float m_cellWidth;

	sf::Vector2f m_position;

	sf::Texture m_texture;

	sf::Sprite m_sprite;

	const std::vector<TState> *m_states;

	std::vector<TState>::const_iterator m_curState;

	TetrominoType randomType();
};

