#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

enum ButtonState
{
	NORMAL,
	HOWERED,
	CLICKED,
	COUNT,
};

class Button
{
public:
	Button(const sf::Vector2f m_position, const std::string text, 
		std::function<void(void)> onClickEvent);

	void update(sf::Window &window);

	const sf::Text& getText() const { return m_texts[m_state]; }

private:
	int m_charSize{ 36 };

	std::string m_text;

	sf::Vector2f m_position;

	std::vector<sf::Text> m_texts;

	sf::Font m_font;

	std::function<void(void)> m_onClickEvent;

	ButtonState m_state = ButtonState::NORMAL;

	void defoultTextInit(sf::Text &txt);
};

