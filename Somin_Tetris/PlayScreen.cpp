#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	
}

const GameScreen PlayScreen::run(sf::RenderWindow &window)
{
	sf::Texture fieldImg;
	fieldImg.loadFromFile(FIELD_IMG_PATH);

	m_sprites.push_back(sf::Sprite());
	m_sprites[m_sprites.size() - 1].setTexture(fieldImg);
	m_sprites[m_sprites.size() - 1].move(FIELD_POSITION);

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
		for (const auto& sprite : m_sprites)
		{
			window.draw(sprite);
		}
		
		window.display();
	}

	return m_curScreen;
}
