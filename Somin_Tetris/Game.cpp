#include "Game.h"

Game::Game(const sf::Vector2f &position)
	: m_position{ position }, 
	m_field{ FIELD_POSITION + m_position, FIELD_SIZE, CELL_WIDTH }
{
	// Load sprites
	m_textures.emplace_back(new sf::Texture{});
	m_textures[m_textures.size() - 1]->loadFromFile(NEXT_TETROMINO_BACKGROUND_IMG_PATH);

	m_sprites.emplace_back(new sf::Sprite{ *m_textures[m_textures.size() - 1] });
	m_sprites[m_textures.size() - 1]->move(m_position + NEXT_TETROMINO_BACKGROUND_POSITION);

	// Create inital tetromines
	m_curTetrominoPos = INIT_TETROMINO_POS;

	m_curTetromino.reset(new Tetromino{ m_field.cellCoordinate(m_curTetrominoPos), CELL_WIDTH});
	m_nextTetromino.reset(new Tetromino{ NEXT_TETROMINO_PX_POS + m_position, CELL_WIDTH });
}

void Game::update()
{
	if (m_isGameOver || m_isPaused) return;
	
	if (m_clock.getElapsedTime().asMilliseconds() > m_stats.getNextDownTime())
	{
		m_clock.restart();

		if (m_field.checkPlace(m_curTetromino->curState(), m_curTetrominoPos + DOWN))
		{
			m_curTetromino->move({ 0, CELL_WIDTH + 1 });
			m_curTetrominoPos += DOWN;
		}
		else if (m_field.checkPlace(m_curTetromino->curState(), m_curTetrominoPos))
		{
			m_field.fixTetromino(*m_curTetromino, m_curTetrominoPos);
			// Next -> Current
			m_curTetromino.reset(m_nextTetromino.release());
			// Next = New
			m_nextTetromino.reset(new Tetromino{ NEXT_TETROMINO_PX_POS + m_position, CELL_WIDTH });
			
			// Prepare new current tetromino
			m_curTetrominoPos = INIT_TETROMINO_POS;
			m_curTetromino->setPosition(m_field.cellCoordinate(m_curTetrominoPos));

			if (m_curTetromino->type() == TetrominoType::I) { m_stats.resetTimeWithoutI(); }
			else { m_stats.increaseTimeWithoutI(); }

			int levelBefore{ m_stats.getLevel() };
			int linesCleared{ m_field.checkLines() };

			if (linesCleared)
			{
				m_stats.update(linesCleared);

				if (m_stats.getLevel() > levelBefore) { MusicManager::playLevelUp(); }
				else if (linesCleared == TETRIS) { MusicManager::playTetris(); }
				else { MusicManager::playDrop(); }
			}
			else
			{
				MusicManager::playDown();
			}
		}
		else
		{
			gameOver();
		}	
	}
}

void Game::up()
{
	if (m_isGameOver || m_isPaused) return;

	if (m_field.checkPlace(m_curTetromino->nextState(), m_curTetrominoPos))
	{
		m_curTetromino->rotate();
		MusicManager::playRotate();
	}
	else
	{
		auto shift{ m_field.findRotationShift(m_curTetromino->nextState(), m_curTetrominoPos) };

		if (m_field.checkPlace(m_curTetromino->nextState(), m_curTetrominoPos + shift))
		{
			m_curTetrominoPos += shift;
			m_curTetromino->rotate();
			m_curTetromino->setPosition(m_field.cellCoordinate(m_curTetrominoPos));
			MusicManager::playRotate();
		}
		else
		{
			MusicManager::playForbidden();
		}
	}
}

void Game::left()
{
	if (m_isGameOver || m_isPaused) return;

	if (m_field.checkPlace(m_curTetromino->curState(), m_curTetrominoPos + LEFT))
	{
		m_curTetrominoPos += LEFT;
		m_curTetromino->setPosition(m_field.cellCoordinate(m_curTetrominoPos));
		MusicManager::playMove();
	}
	else
	{
		MusicManager::playForbidden();
	}
}

void Game::right()
{
	if (m_isGameOver || m_isPaused) return;

	if (m_field.checkPlace(m_curTetromino->curState(), m_curTetrominoPos + RIGHT))
	{
		m_curTetrominoPos += RIGHT;
		m_curTetromino->setPosition(m_field.cellCoordinate(m_curTetrominoPos));
		MusicManager::playMove();
	}
	else
	{
		MusicManager::playForbidden();
	}
}

void Game::down()
{
	if (m_isGameOver || m_isPaused) return;

	if (m_field.checkPlace(m_curTetromino->curState(), m_curTetrominoPos + DOWN))
	{
		m_curTetrominoPos += DOWN;
		m_curTetromino->setPosition(m_field.cellCoordinate(m_curTetrominoPos));
		m_clock.restart();
		MusicManager::playMove();
	}
}

void Game::draw(sf::RenderWindow &window)
{
	if (!m_isPaused) { update(); }

	// Draw images
	for (const auto &el : m_sprites)
	{
		window.draw(*el);
	}

	// Draw fixed blocks
	m_field.draw(window);

	// Draw tetromines
	m_curTetromino->draw(window);
	m_nextTetromino->draw(window);
}

void Game::gameOver()
{
	m_stats.save();
	m_isGameOver = true;
	MusicManager::playGameOver();
}

void Game::restart()
{
	if (!isGameOver())
	{
		gameOver();
	}

	m_field.clear();

	m_stats.clear();
	m_stats.read();

	m_curTetrominoPos = INIT_TETROMINO_POS;

	m_curTetromino.reset(new Tetromino{ m_field.cellCoordinate(m_curTetrominoPos), CELL_WIDTH });
	m_nextTetromino.reset(new Tetromino{ NEXT_TETROMINO_PX_POS + m_position, CELL_WIDTH });

	m_isGameOver = false;
	m_isPaused = false;

	m_clock.restart();
}

void Game::pause_start()
{
	if (m_isPaused)
	{
		m_clock.restart();
	}

	m_isPaused = !m_isPaused;
}
