#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <random> 

#include "TetrominosStates.h"

enum TetrominoType { O, J, L, T, S, Z, I, TETROMINO_TYPES_COUNT, RANDOM, NONE, };

const std::vector<std::string> BLOCKS_PATH{	"Img\\O.png", 
											"Img\\J.png",
											"Img\\L.png",
											"Img\\T.png",
											"Img\\S.png",
											"Img\\Z.png",
											"Img\\I.png"  };

class Tetromino
{
public:
	Tetromino(const sf::Vector2f &position, float cellWidth, TetrominoType type = RANDOM);

	void draw(sf::RenderWindow &window);

	void move(const sf::Vector2f &delta) { m_position += delta; }

	void setPosition(const sf::Vector2f &pos) { m_position = pos; }

	const sf::Vector2f& getPosition() { return m_position; }

	void rotate();

	const TState& curState() const { return *m_curState; }

	const TState& nextState() const;

	const TetrominoType type() const { return m_type; }

private:
	const float m_cellWidth;

	TetrominoType m_type;

	sf::Vector2f m_position;

	sf::Texture m_texture;

	sf::Sprite m_sprite;

	const std::vector<TState> *m_states;

	std::vector<TState>::const_iterator m_curState;

	static TetrominoType randomType();
};

