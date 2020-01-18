#include "MenuScreen.h"

#include "Screens.h"
#include "Settings.h"
#include "PopoutFrame.h"

MenuScreen::MenuScreen()
{
	MusicManager::updateMusicMode();

	m_screenSaver.reset( new ScreenSaver );
}

GameScreen const MenuScreen::run(sf::RenderWindow &window)
{
	sf::Event event;

	m_curScreen = GameScreen::MENU;

	makePopoutMenu();

	while (m_curScreen == GameScreen::MENU)
	{
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return (GameScreen::EXIT);
			}
			else if (event.type == sf::Event::Resized)
			{
				float newHeight((float)event.size.width);
				newHeight /= WINDOW_WIDTH;
				newHeight *= WINDOW_HEIGHT;
				window.setSize({ event.size.width, static_cast<unsigned>(newHeight) });
			}
		}

		//Clearing screen
		window.clear(WINDOW_BACKGROUND);

		//Drawing
		m_screenSaver->draw(window);

		m_popoutFrame->draw(window);
		
		window.display();
	}

	return m_curScreen;
}

void MenuScreen::makePopoutMenu()
{
	PopoutFrame *menu{ new PopoutFrame{ MENU_FRAME_POSITION, "SOMIN TETRIS" } };

	menu->push("Play", [&]() { startGame(); });

	Button *btn = new Button(sf::Vector2f(), Settings::getPlayMode());
	btn->setOnclickEvent([&, btn]()
	{
		btn->setText(Settings::nextPlayMode());
	});
	menu->push(btn);

	btn = new Button(sf::Vector2f(), Settings::getMusicMode());
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
	menu->push(btn);

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
	menu->push(btn);

	menu->push("Stats", [&]() { makePopoutStats(); });

	m_popoutFrame.reset(menu);
}

void MenuScreen::makePopoutStats()
{
	PopoutFrame* stats{ new PopoutFrame{ STATS_FRAME_POSITION, "Statistics" } };
	
	stats->push(std::string{ "Max score: " } + std::to_string(Settings::getMaxScore()));
	stats->push(std::string{ "Max line: " } + std::to_string(Settings::getMaxLine()));
	stats->push(std::string{ "Max level: " } + std::to_string(Settings::getMaxLevel()));
	stats->push(std::string{ "Max time without I: " } + std::to_string(Settings::getMaxTimeWithoutI()));

	stats->push("Back", [&]() { makePopoutMenu(); });

	m_popoutFrame.reset(stats);
}
