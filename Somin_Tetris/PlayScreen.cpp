#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	
}

const GameScreen PlayScreen::run(sf::RenderWindow &window)
{
	sf::Texture fieldImg;
	fieldImg.loadFromFile(FIELD_IMG_PATH);

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
		}

		//Clearing screen
		window.clear(WINDOW_BACKGROUND);

		

		//Drawing

		
		window.display();
	}

	return m_curScreen;
}
