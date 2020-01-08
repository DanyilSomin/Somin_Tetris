#include "MenuScreen.h"

#include "Screens.h"
#include "Settings.h"

MenuScreen::MenuScreen()
{
	Button *btn = new Button(sf::Vector2f((WINDOW_WIDTH / 2), PLAY_BTN_HEIGHT),
		"Play",
		[]() 
		{
			//Settings::nextPlayMode();
		}
	);

	m_buttons.emplace_back(btn);

	btn = new Button(sf::Vector2f((WINDOW_WIDTH / 2), MODE_BTN_HEIGHT), Settings::getPlayMode());
	btn->setOnclickEvent([btn]() 
	{ 
		btn->setText(Settings::nextPlayMode()); 
	});

	m_buttons.emplace_back(btn);
}

GameScreen MenuScreen::run(sf::RenderWindow &window)
{
	sf::Event event;

	m_curScreen = GameScreen::MENU;

	while (m_curScreen == GameScreen::MENU)
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
		window.clear();

		//Drawing
		for (auto &btn : m_buttons)
		{
			btn->update(window);
			window.draw(btn->getText());
		}
		
		window.display();
	}

	return m_curScreen;
}