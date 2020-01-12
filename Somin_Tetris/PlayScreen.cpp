#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	// Initialise texts
	m_font.loadFromFile("Fonts\\Schlange_sans_bld.otf");

	for (int i{ 0 }; i < TextType::COUNT; ++i)
	{
		m_texts.emplace_back(new sf::Text);
		m_texts[i]->setPosition(TEXTS_POSITIONS[i]);
		m_texts[i]->setCharacterSize(m_charSize);
		m_texts[i]->setFont(m_font);
		m_texts[i]->setFillColor(sf::Color::White);
	}


}

const GameScreen PlayScreen::run(sf::RenderWindow &window)
{
	m_game.reset( new Game{ GAME_POSITION } );

	m_curScreen = GameScreen::PLAY;

	return mainLoop(window);
}

const GameScreen PlayScreen::mainLoop(sf::RenderWindow &window)
{

	while (m_curScreen == GameScreen::PLAY)
	{
		handleEvents(window);

		//Clearing screen
		window.clear(WINDOW_BACKGROUND);

		//Drawing
		m_game->draw(window);

		updateText();
		for (auto &text : m_texts)
		{
			window.draw(*text);
		}
		
		window.display();
	}

	return m_curScreen;
}

void PlayScreen::handleEvents(sf::RenderWindow &window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		// Window closed
		if (event.type == sf::Event::Closed)
		{
			m_curScreen = GameScreen::EXIT;
		}
		else if ((event.type == sf::Event::KeyPressed)
			&& ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::A)))
		{
			m_game->left();
		}
		else if ((event.type == sf::Event::KeyPressed)
			&& ((event.key.code == sf::Keyboard::Right) || (event.key.code == sf::Keyboard::D)))
		{
			m_game->right();
		}
		else if ((event.type == sf::Event::KeyPressed)
			&& ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W)))
		{
			m_game->up();
		}
		else if ((event.type == sf::Event::KeyPressed)
			&& ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S)))
		{
			m_game->down();
		}
		else if (event.type == sf::Event::Resized)
		{
			float newHeight(event.size.width);
			newHeight /= WINDOW_WIDTH;
			newHeight *= WINDOW_HEIGHT;
			window.setSize({ event.size.width, static_cast<unsigned>(newHeight) });
		}
	}
}

void PlayScreen::updateText()
{
	m_texts[TextType::SCORE]->setString(std::string{ "Score: " } + std::to_string(m_game->getStats().score));
	m_texts[TextType::LEVEL]->setString(std::string{ "Level: " } + std::to_string(m_game->getStats().level));
	m_texts[TextType::LINE]->setString(std::string{ "Line: " } + std::to_string(m_game->getStats().line));

	int TRT{ 0 };
	if (m_game->getStats().line) 
	{ 
		TRT = static_cast<float>(m_game->getStats().tetrisLinesAmount) / m_game->getStats().line * 100;
	}
	m_texts[TextType::TETRIS_RATE]->setString(std::string{ "TRT: " } + std::to_string(TRT));

	m_texts[TextType::TIME_WITHOUT_I]->setString(std::string{ "Without I: " } + std::to_string(m_game->getStats().timeWithoutI));
}
