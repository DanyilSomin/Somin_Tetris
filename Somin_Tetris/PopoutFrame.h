#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <algorithm>

#include "Button.h"

constexpr int HEADER_FONT_SIZE{ 36 };
constexpr int FONT_SIZE{ 24 };

constexpr float DISTANSE_BETWEEN{ 15 };

const sf::Vector2f BORDER_SIZE{ 20, 20 };

const sf::Color RECTANGLE_COLOR{ sf::Color{0, 0, 0, 200} };

class PopoutFrame
{
public:
	PopoutFrame(const sf::Vector2f &position, const std::string &header);

	void draw(sf::RenderWindow &window);

	void setColor(const sf::Color &color) { m_color = color; }
	
	void push(const std::string &str);
	void push(Button * btn);
	void push(const std::string &str, const std::function<void()> &onClick);

private:
	sf::Font m_font;

	sf::Color m_color{ RECTANGLE_COLOR };

	sf::RectangleShape m_rectangle;
	
	sf::Vector2f m_size;
	sf::Vector2f m_position;

	std::vector<std::unique_ptr<sf::Text>> m_texts;
	std::vector<std::unique_ptr<Button>> m_buttons;

	void resizeToFit();

	void alignCenter();
	
	void update(sf::RenderWindow &window);
};

