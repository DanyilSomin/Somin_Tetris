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

	m_pauseFrame.reset(new PopoutFrame{ PAUSE_FRAME_POSITION, "GAME PAUSED" });
	m_pauseFrame->push("Restart", [&]() { m_game->restart(); });
	m_pauseFrame->push("Main menu", [&]() { goToMenu(); });
	auto btn = new Button(sf::Vector2f(), Settings::getMusicMode());
	btn->setOnclickEvent([&, btn]()
	{
		if (Settings::isMusicMuted())
		{
			btn->setText(Settings::unmuteMusic());
		}
		else
		{
			btn->setText(Settings::muteMusic());
		}
		MusicManager::updateMusicMode();
	});
	m_pauseFrame->push(btn);

	btn = new Button(sf::Vector2f(), Settings::getSoundMode());
	btn->setOnclickEvent([&, btn]()
	{
		if (Settings::isSoundMuted())
		{
			btn->setText(Settings::unmuteSound());
		}
		else
		{
			btn->setText(Settings::muteSound());
		}
		MusicManager::updateMusicMode();
	});
	m_pauseFrame->push(btn);

	m_pauseFrame->push("Back to game", [&]() { m_game->pause_start(); });

	m_gameOverFrame.reset(new PopoutFrame{ PAUSE_FRAME_POSITION, "GAME OVER" });
	m_gameOverFrame->push("Play again", [&]() { m_game->restart(); });

	m_gameOverFrame->push("Main menu", [&]() { goToMenu(); });

	m_pauseBtn.reset(new Button{ PAUSE_BTN_POSITION, "Pause", [&]() 
	{ 
		m_game->pause_start(); MusicManager::playPause(); 
	} });
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

		m_pauseBtn->draw(window);

		if (m_game->isGameOver())
		{
			m_gameOverFrame->draw(window);
		}
		else if (m_game->isPaused())
		{
			m_pauseFrame->draw(window);
		}
		
		window.display();
	}

	return m_curScreen;
}

void PlayScreen::goToMenu()
{
	if (!m_game->isGameOver())
	{
		m_game->gameOver();
	}

	m_curScreen = GameScreen::MENU;
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
			float newHeight((float)event.size.width);
			newHeight /= WINDOW_WIDTH;
			newHeight *= WINDOW_HEIGHT;
			window.setSize({ event.size.width, static_cast<unsigned>(newHeight) });
		}
		else if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::R)
		{
			m_game->restart();
		}
		else if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::P)
		{
			m_pauseBtn->click();
		}
	}
}

void PlayScreen::updateText()
{
	m_texts[TextType::SCORE]->setString(std::string{ "Score: " } + std::to_string(m_game->getStats().getScore()));
	m_texts[TextType::LEVEL]->setString(std::string{ "Level: " } + std::to_string(m_game->getStats().getLevel()));
	m_texts[TextType::LINE]->setString(std::string{ "Line: " } + std::to_string(m_game->getStats().getLine()));
	m_texts[TextType::TETRIS_RATE]->setString(std::string{ "TRT: " } + std::to_string(m_game->getStats().getTetrisRate()));
	m_texts[TextType::TIME_WITHOUT_I]->setString(std::string{ "Without I: " } + std::to_string(m_game->getStats().getTimeWithoutI()));
}
