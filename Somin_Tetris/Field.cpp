#include "Field.h"

Field::Field(const sf::Vector2f &position, const sf::Vector2i &size, float cellWidth)
	: m_position{ position }, m_size{ size }, m_cellWidth{ cellWidth }
{
	for (int i{ 0 }; i < TETROMINO_TYPES_COUNT; ++i)
	{
		m_blocksTextures.emplace_back(new sf::Texture{});
		m_blocksTextures[i]->loadFromFile(BLOCKS_PATH[i]);

		m_blocksSprites.emplace_back(new sf::Sprite{ *m_blocksTextures[i] });
	}

	m_fieldTexture.reset(new sf::Texture{});
	m_fieldTexture->loadFromFile(FIELD_IMG_PATH);

	m_fieldSprite.reset(new sf::Sprite{ *m_fieldTexture });
	m_fieldSprite->move(m_position);
}

void Field::draw(sf::RenderWindow & window)
{
	window.draw(*m_fieldSprite);

	for (int i{ 0 }; i < (int)m_lines.size(); ++i)
	{
		for (int j{ 0 }; j < m_size.x; ++j)
		{
			sf::Sprite *sprite = nullptr;
			switch (m_lines[i][j])
			{
			case O: sprite = m_blocksSprites[O].get(); break;
			case J: sprite = m_blocksSprites[J].get(); break;
			case L: sprite = m_blocksSprites[L].get(); break;
			case T: sprite = m_blocksSprites[T].get(); break;
			case S: sprite = m_blocksSprites[S].get(); break;
			case Z: sprite = m_blocksSprites[Z].get(); break;
			case I: sprite = m_blocksSprites[I].get(); break;
			}

			if (sprite)
			{
				sprite->setPosition(cellCoordinate({ j, m_size.y - 1 - i }));
				window.draw(*sprite);
			}

		}
	}
}

bool Field::checkPlace(const TState & state, const sf::Vector2i &position) const
{
	// Collision with walls
	for (int i{ 0 }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			// left
			if ((j + position.x) < 0 && state[i][j]) { return false; }
			// right
			if ((j + position.x) >= m_size.x && state[i][j]) { return false; }
			// bottom
			if ((i + position.y) >= m_size.y && state[i][j]) { return false; }
		}
	}

	int linesAmount(m_lines.size());
	int upBorder{ std::min(m_size.y - 1, position.y + TETROMINO_STATE_WIDTH - 1) };
	int downBorder{ std::max(m_size.y - linesAmount, position.y) };
	for (int i{ downBorder }; i <= upBorder; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[i - position.y][j])
				if (m_lines[m_size.y - 1 - i][j + position.x] != NONE)
				{
					return false;
				}
		}
	}

	return true;
}

bool Field::fixTetromino(const Tetromino &tetromino, const sf::Vector2i &position = { 0, 0 })
{
	// Create new lines if they do not exist
	for (int i(m_lines.size()); i < m_size.y - position.y; ++i)
	{
		m_lines.push_back(std::vector<TetrominoType>( m_size.x, TetrominoType::NONE ));
	}
	if ((int)m_lines.size() > m_size.y) { return false; }

	// Write information about new blocks to the field
	for (int i{ 0 }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (tetromino.curState()[i][j])
			{
				m_lines[(m_size.y - 1 - i) - position.y][j + position.x]
					= tetromino.type();
			}
		}
	}

	return true;
}

const sf::Vector2i Field::findRotationShift(const TState &state, const sf::Vector2i &position)
{
	int leftmostI = TETROMINO_STATE_WIDTH - 1;
	int rightmostI = 0;

	for (int i{ TETROMINO_STATE_WIDTH - 1 }; i >= 0; --i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[j][i]) { leftmostI = i; break; }
		}
	}

	for (int i{ 1 }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[j][i]) { rightmostI = i; break; }
		}
	}

	if ((leftmostI + position.x) < 0)
	{
		return { -(leftmostI + position.x), 0 };
	}

	if ((rightmostI + position.x) >= m_size.x)
	{
		return { (m_size.x - (rightmostI + position.x) - 1), 0 };
	}

	return sf::Vector2i{ 0, 0 };
}

const sf::Vector2f Field::cellCoordinate(const sf::Vector2i & cell)
{
	sf::Vector2f coordinates = BORDER_WIDTH + m_position;

	coordinates.x += (m_cellWidth + 1) * cell.x;
	coordinates.y += (m_cellWidth + 1) * cell.y;

	return coordinates;
}

int Field::checkLines()
{
	int count{ 0 };

	for (auto it{ m_lines.begin() }; it < m_lines.end(); )
	{
		bool flag{ true };

		for (const auto& el : *it)
		{
			if (el == NONE)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			it = m_lines.erase(it);
			++count;
		}
		else
		{
			++it;
		}
	}

	return count;
}
