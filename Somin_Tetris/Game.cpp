#include "Game.h"

Game::Game(const sf::Vector2f &position)
	: m_position{ position }, m_startLevel{ Settings::getPlayDifficulty().first }
{
	// Get settings
	m_stats.level = m_startLevel;
	m_linesBeforeNextLevel = Settings::getPlayDifficulty().second;
	m_nextDownTime = LEVEL_PERIODS[std::min(static_cast<int>(LEVEL_PERIODS.size() - 1), m_stats.level)];

	// Load sprites
	m_textures.emplace_back(new sf::Texture{});
	m_textures[m_textures.size() - 1]->loadFromFile(FIELD_IMG_PATH);

	m_sprites.emplace_back(new sf::Sprite{ *m_textures[m_textures.size() - 1] });
	m_sprites[m_textures.size() - 1]->move(m_position + FIELD_POSITION);

	m_textures.emplace_back(new sf::Texture{});
	m_textures[m_textures.size() - 1]->loadFromFile(NEXT_TETROMINO_BACKGROUND_IMG_PATH);

	m_sprites.emplace_back(new sf::Sprite{ *m_textures[m_textures.size() - 1] });
	m_sprites[m_textures.size() - 1]->move(m_position + NEXT_TETROMINO_BACKGROUND_POSITION);

	// Create inital tetromines
	for (int i{ 0 }; i < TETROMINO_TYPES_COUNT; ++i)
	{
		m_blocksTextures.emplace_back(new sf::Texture{});
		m_blocksTextures[i]->loadFromFile(BLOCKS_PATH[i]);

		m_blocksSprites.emplace_back(new sf::Sprite{ *m_blocksTextures[i] });
	}

	m_curTetrominoPos = INIT_TETROMINO_POS;

	m_curTetromino.reset(new Tetromino{ cellCoordinate(m_curTetrominoPos), CELL_WIDTH});
	m_nextTetromino.reset(new Tetromino{ NEXT_TETROMINO_PX_POS + m_position, CELL_WIDTH });
}

void Game::update()
{
	if (m_gameOver) return;

	m_stats.line += checkLines();

	if (m_clock.getElapsedTime().asMilliseconds() > m_nextDownTime)
	{
		m_clock.restart();

		if (checkPlace(m_curTetromino->curState(), m_curTetrominoPos + DOWN))
		{
			m_curTetromino->move({ 0, CELL_WIDTH + 1 });
			m_curTetrominoPos.x++;
		}
		else
		{
			if (checkPlace(m_curTetromino->curState(), m_curTetrominoPos))
			{
				fixCurrentTetromino();
				// Next -> Current
				m_curTetromino.reset(m_nextTetromino.release());
				// Next = New
				m_nextTetromino.reset(new Tetromino{ NEXT_TETROMINO_PX_POS + m_position, CELL_WIDTH });
			
				// Prepare new current tetromino
				m_curTetrominoPos = INIT_TETROMINO_POS;
				m_curTetromino->setPosition(cellCoordinate(m_curTetrominoPos));

				if (m_curTetromino->type() == TetrominoType::I) { m_stats.timeWithoutI = 0; }
				else { ++m_stats.timeWithoutI; }
			}
			else
			{
				m_gameOver == true;
			}
		}
	}
}

void Game::up()
{
	if (checkPlace(m_curTetromino->nextState(), m_curTetrominoPos))
	{
		m_curTetromino->rotate();
	}
	else
	{
		auto shift{ findRotationShift() };

		if (checkPlace(m_curTetromino->nextState(), m_curTetrominoPos + shift))
		{
			m_curTetrominoPos += shift;
			m_curTetromino->rotate();
			m_curTetromino->setPosition(cellCoordinate(m_curTetrominoPos));
		}
	}
}

void Game::left()
{
	if (checkPlace(m_curTetromino->curState(), m_curTetrominoPos + LEFT))
	{
		m_curTetrominoPos += LEFT;
		m_curTetromino->setPosition(cellCoordinate(m_curTetrominoPos));
	}
}

void Game::right()
{
	if (checkPlace(m_curTetromino->curState(), m_curTetrominoPos + RIGHT))
	{
		m_curTetrominoPos += RIGHT;
		m_curTetromino->setPosition(cellCoordinate(m_curTetrominoPos));
	}
}

void Game::down()
{
	if (checkPlace(m_curTetromino->curState(), m_curTetrominoPos + DOWN))
	{
		m_curTetrominoPos += DOWN;
		m_curTetromino->setPosition(cellCoordinate(m_curTetrominoPos));
		m_clock.restart();
	}
}

const sf::Vector2i Game::findRotationShift()
{
	auto &state{ m_curTetromino->nextState() };

	int leftmostI = TETROMINO_STATE_WIDTH - 1;
	int rightmostI = 0;

	for (int i{ TETROMINO_STATE_WIDTH - 2 }; i >= 0; --i)
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

	if ((leftmostI + m_curTetrominoPos.y) < 0)
	{
		return { 0, -(leftmostI + m_curTetrominoPos.y) };
	}

	if ((rightmostI + m_curTetrominoPos.y) >= FIELD_WIDTH)
	{
		return { 0, (FIELD_WIDTH - (rightmostI + m_curTetrominoPos.y) - 1) };
	}

	return sf::Vector2i{ 0, 0 };
}

void Game::draw(sf::RenderWindow &window)
{
	update();

	// Draw images
	for (const auto &el : m_sprites)
	{
		window.draw(*el);
	}

	// Draw fixed blocks
	for (int i{ 0 }; i < m_lines.size(); ++i)
	{
		for (int j{ 0 }; j < FIELD_WIDTH; ++j)
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
				sprite->setPosition(cellCoordinate( { FIELD_HEIGHT - 1 - i, j } ));
				window.draw(*sprite);
			}

		}
	}

	// Draw tetromines
	m_curTetromino->draw(window);
	m_nextTetromino->draw(window);
}

void Game::fixCurrentTetromino()
{
	// Create new lines if they do not exist
	for (int i( m_lines.size() ); i < FIELD_HEIGHT - m_curTetrominoPos.x; ++i)
	{
		m_lines.push_back({});
		m_lines[m_lines.size() - 1].fill(TetrominoType::NONE);
	}
	if (m_lines.size() > FIELD_HEIGHT) { gameOver(); return; }

	// Write information about new blocks to the field
	for (int i{ 0 }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (m_curTetromino->curState()[i][j])
			{
				m_lines[(FIELD_HEIGHT - 1 - i) - m_curTetrominoPos.x][j + m_curTetrominoPos.y]
					= m_curTetromino->type();
			}
		}
	}
}

bool Game::checkPlace(const TState & state, const sf::Vector2i &delta) const
{
	// Check for walls
		// Left wall
	for (int i{ delta.y }; i < 0; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[j][-i - 1]) { return false; }
		}
	}
		// Right wall
	for (int i{ FIELD_WIDTH - TETROMINO_STATE_WIDTH - delta.y }; i < 0; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[j][TETROMINO_STATE_WIDTH + i]) { return false; }
		}
	}
		// Bottom wall
	for (int i{ FIELD_HEIGHT - delta.x }; i < TETROMINO_STATE_WIDTH; ++i)
	{
		for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
		{
			if (state[i][j]) { return false; }
		}
	}

	// Tetromino is in bounds
		// Check for other blocks
	{
		int linesAmount( m_lines.size() );
		int upBorder{ std::min(FIELD_HEIGHT - 1, delta.x + TETROMINO_STATE_WIDTH - 1) };
		int downBorder{ std::max(FIELD_HEIGHT - linesAmount, delta.x) };
		for (int i{ downBorder }; i <= upBorder; ++i)
		{
			for (int j{ 0 }; j < TETROMINO_STATE_WIDTH; ++j)
			{
				if (state[i - delta.x][j])
					if (m_lines[FIELD_HEIGHT - 1 - i][j + delta.y] != NONE)
					{
						return false;
					}
			}
		}
	}

	return true;
}

const sf::Vector2f Game::cellCoordinate(const sf::Vector2i & cell)
{
	sf::Vector2f coordinates = BORDER_WIDTH + m_position;

	coordinates.x += (CELL_WIDTH + 1) * cell.y;
	coordinates.y += (CELL_WIDTH + 1) * cell.x;

	return coordinates;
}

int Game::checkLines()
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

	if (count)
	{
		m_stats.level = m_stats.line / m_linesBeforeNextLevel + m_startLevel;
		
		m_nextDownTime = LEVEL_PERIODS[std::min(static_cast<int>(LEVEL_PERIODS.size() - 1), m_stats.level)];
		
		if (count == TETRIS) { m_stats.tetrisLinesAmount += TETRIS; }
		
		m_stats.score += SCORE_POINTS_COEF[count] * (m_stats.level + 1);
	}

	return count;
}
