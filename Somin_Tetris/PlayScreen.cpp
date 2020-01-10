#include "PlayScreen.h"

PlayScreen::PlayScreen()
	: m_game{ GAME_POSITION }
{
	
}

const GameScreen PlayScreen::run(sf::RenderWindow &window)
{
	m_curScreen = GameScreen::PLAY;

	return mainLoop(window);
}

const GameScreen PlayScreen::mainLoop(sf::RenderWindow &window)
{
	sf::Event event;

	while (m_curScreen == GameScreen::PLAY)
	{
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return (GameScreen::EXIT);
			}
			else if ((event.type == sf::Event::KeyPressed)
				&& ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::A)))
			{
				m_game.left();
			}
			else if ((event.type == sf::Event::KeyPressed)
				&& ((event.key.code == sf::Keyboard::Right) || (event.key.code == sf::Keyboard::D)))
			{
				m_game.right();
			}
			else if ((event.type == sf::Event::KeyPressed)
				&& ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W)))
			{
				m_game.up();
			}
			else if ((event.type == sf::Event::KeyPressed)
				&& ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S)))
			{
				m_game.down();
			}
		}

		//Clearing screen
		window.clear(WINDOW_BACKGROUND);

		

		//Drawing
		m_game.draw(window);
		
		window.display();
	}

	return m_curScreen;
}
