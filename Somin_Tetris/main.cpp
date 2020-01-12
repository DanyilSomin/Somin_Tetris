#include <random>
#include <ctime>

#include <SFML/Graphics.hpp>
#include "Screens.h"

int main()
{
	std::srand(std::time(nullptr));

	//Applications variables
	std::vector<Screen*> screens;
	GameScreen screen = GameScreen::MENU;

	//Window creation
	sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		"Somin Tetris: best clone ever!");
	
	mainWindow.setFramerateLimit(FRAMERATE);

	//Screens preparations
	MenuScreen menu;
	screens.push_back(&menu);
	PlayScreen playScreen;
	screens.push_back(&playScreen);

	//Main loop
	while (screen != GameScreen::EXIT)
	{
		screen = screens[screen]->run(mainWindow);
	}

	return EXIT_SUCCESS;
}