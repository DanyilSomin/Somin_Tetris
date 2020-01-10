#include "Tetromino.h"

Tetromino::Tetromino(const sf::Vector2f & position, float cellWidth, TetrominoType type)
	: m_position{ position }, m_cellWidth{ cellWidth }, m_type{ type }
{
	if (m_type == RANDOM)
	{
		m_type = randomType();
	}
	// Load sprite
	switch (m_type)
	{
	case O:
		m_states = &OStates;
		m_texture.loadFromFile(BLOCKS_PATH[O]);
		break;
	case J:
		m_states = &JStates;
		m_texture.loadFromFile(BLOCKS_PATH[J]);
		break;
	case L:
		m_states = &LStates;
		m_texture.loadFromFile(BLOCKS_PATH[L]);
		break;
	case T:
		m_states = &TStates;
		m_texture.loadFromFile(BLOCKS_PATH[T]);
		break;
	case S:
		m_states = &SStates;
		m_texture.loadFromFile(BLOCKS_PATH[S]);
		break;
	case Z:
		m_states = &ZStates;
		m_texture.loadFromFile(BLOCKS_PATH[Z]);
		break;
	case I:
		m_states = &IStates;
		m_texture.loadFromFile(BLOCKS_PATH[I]);
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
	// Just pick next state
	++m_curState;
	if (m_curState == m_states->end())
	{
		m_curState = m_states->begin();
	}
}

const TState & Tetromino::nextState() const
{
	auto it = m_curState;
	++it;
	if (it == m_states->end())
	{
		it = m_states->begin();
	}

	return *it;
}

TetrominoType Tetromino::randomType()
{
	return static_cast<TetrominoType>(std::rand() % TetrominoType::TETROMINO_TYPES_COUNT);
}
