#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.h"

class PopoutFrame
{
public:
	void draw(sf::RenderWindow &window);

	void push(const sf::Text &text);;
};

