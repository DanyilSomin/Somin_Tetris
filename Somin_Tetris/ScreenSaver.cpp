#include "ScreenSaver.h"

ScreenSaver::ScreenSaver()
{
	updateSpeed();

	initTetrominos();
}

void ScreenSaver::draw(sf::RenderWindow & window)
{
	update();

	for (auto &tetromino : m_tetrominos)
	{
		tetromino->draw(window);
	}
}

void ScreenSaver::update()
{
	for (auto &tetromino : m_tetrominos)
	{
		if (!(std::rand() % ROTATE_CHANCE))
		{
			tetromino->rotate();
		}
	}

	if (m_clock.getElapsedTime().asMilliseconds() > m_deltaTime)
	{
		m_clock.restart();

		updateSpeed();

		for (auto &tetromino : m_tetrominos)
		{
			tetromino->move({ 0, SCREENSAWER_CELL_WIDTH });
			
			if (tetromino->getPosition().y > WINDOW_HEIGHT + (SCREENSAWER_CELL_WIDTH * TETROMINO_STATE_WIDTH))
			{
				int verticalShift{ (int)((1 + WINDOW_HEIGHT / SPASE_BETWEEN_TETROMINOS) * SPASE_BETWEEN_TETROMINOS) };

				tetromino.reset( new Tetromino{
					{ tetromino->getPosition().x, 
					  tetromino->getPosition().y - verticalShift },
						SCREENSAWER_CELL_WIDTH });
			}
		}
	}
}

void ScreenSaver::initTetrominos()
{
	for (float i = 0;
		i < WINDOW_WIDTH + SCREENSAWER_CELL_WIDTH * TETROMINO_STATE_WIDTH;
		i += SPASE_BETWEEN_TETROMINOS)
	{
		for (float j = 0; j < WINDOW_HEIGHT; j += SPASE_BETWEEN_TETROMINOS)
		{
			m_tetrominos.emplace_back(new Tetromino{ sf::Vector2f(i, j), SCREENSAWER_CELL_WIDTH });
		}
	}
}
