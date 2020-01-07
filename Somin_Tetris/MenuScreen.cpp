#include "Screens.h"

MenuScreen::MenuScreen()
{
	m_buttons.emplace_back( new Button(sf::Vector2f((WINDOW_WIDTH / 2), PLAY_BTN_HEIGHT), 
		"Play",
		[this]() { 
			this->whatever(); 
		}
	));
}

void MenuScreen::whatever() const
{
	std::pair<int, int> k{1, 2};
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