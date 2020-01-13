#include "MenuScreen.h"

#include "Screens.h"
#include "Settings.h"
#include "PopoutFrame.h"

MenuScreen::MenuScreen()
{
	m_popoutFrame.reset(new PopoutFrame{ MENU_FRAME_POSITION, "TETRIS" });
	
	m_popoutFrame->push("Play", [&]() { this->startGame(); });

	Button *btn = new Button(sf::Vector2f((WINDOW_WIDTH / 2), 100), Settings::getPlayMode());
	btn->setOnclickEvent([btn]() 
	{ 
		btn->setText(Settings::nextPlayMode()); 
	});

	m_popoutFrame->push(btn);

}

GameScreen const MenuScreen::run(sf::RenderWindow &window)
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
			else if (event.type == sf::Event::Resized)
			{
				float newHeight(event.size.width);
				newHeight /= WINDOW_WIDTH;
				newHeight *= WINDOW_HEIGHT;
				window.setSize({ event.size.width, static_cast<unsigned>(newHeight) });
			}
		}

		//Clearing screen
		window.clear(WINDOW_BACKGROUND);

		//Drawing
		m_popoutFrame->draw(window);
		
		window.display();
	}

	return m_curScreen;
}