#include "Tetromino.h"

Tetromino::Tetromino(const sf::Vector2f & position, float cellWidth, TetrominoType type)
	: m_position{ position }, m_cellWidth{ cellWidth }
{
	int m_type = type;

	if (m_type == RANDOM)
	{
		m_type = randomType();
	}

	switch (m_type)
	{
	case O:
		m_states = &OStates;
		m_texture.loadFromFile(O_IMG_PATH);
		break;
	case J:
		m_states = &JStates;
		m_texture.loadFromFile(J_IMG_PATH);
		break;
	case L:
		m_states = &LStates;
		m_texture.loadFromFile(L_IMG_PATH);
		break;
	case T:
		m_states = &TStates;
		m_texture.loadFromFile(T_IMG_PATH);
		break;
	case S:
		m_states = &SStates;
		m_texture.loadFromFile(S_IMG_PATH);
		break;
	case Z:
		m_states = &ZStates;
		m_texture.loadFromFile(Z_IMG_PATH);
		break;
	case I:
		m_states = &IStates;
		m_texture.loadFromFile(I_IMG_PATH);
		break;
	}

	m_sprite.setTexture(m_texture);

	m_curState = m_states->begin();
}

void Tetromino::draw(sf::RenderWindow & window)
{
	for (size_t i{ 0 }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (size_t j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if ((*m_curState)[i][j])
			{
				// NOTE: j is first argument
				sf::Vector2f relative_pos{ j + (m_cellWidth * j), i + (m_cellWidth * i)};
				//

				m_sprite.setPosition(m_position + relative_pos);
				window.draw(m_sprite);
			}
		}
	}
}

void Tetromino::rotate()
{
	++m_curState;
	if (m_curState == m_states->end())
	{
		m_curState = m_states->begin();
	}
}

TetrominoType Tetromino::randomType()
{
	return static_cast<TetrominoType>(std::rand() % TetrominoType::TETROMINO_TYPES_COUNT);
}
