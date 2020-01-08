#include "Button.h"

Button::Button(const sf::Vector2f position, 
	const std::string &text, 
	const std::function<void(void)> &onClickEvent)
	: m_position{ position }, m_onClickEvent{ onClickEvent }, m_text{ text }
{
	m_font.loadFromFile("Fonts\\Schlange_sans_bld.otf");

	setText(text);
}

void Button::setText(const std::string &text)
{
	m_texts.resize(ButtonState::COUNT);

	m_text = text;

	for (auto &txt : m_texts)
	{
		defoultTextInit(txt);
	}

	m_texts[ButtonState::NORMAL].setFillColor(sf::Color::White);
	m_texts[ButtonState::HOWERED].setFillColor(sf::Color(200, 200, 200, 255));
	m_texts[ButtonState::CLICKED].setFillColor(sf::Color(160, 160, 160, 255));
}

void Button::update(sf::Window &window)
{
	if (m_texts[m_state].getGlobalBounds().contains(
		static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (m_state != ButtonState::CLICKED)
			{
				m_state = ButtonState::CLICKED;
				m_onClickEvent();
			}
		}
		else
		{
			m_state = ButtonState::HOWERED;
		}
	}
	else
	{
		m_state = ButtonState::NORMAL;
	}
}

void Button::defoultTextInit(sf::Text &txt)
{
	txt.setCharacterSize(m_charSize);
	txt.setFont(m_font);
	txt.setString(m_text);
	txt.setPosition(m_position);
	txt.setFillColor(sf::Color::White);
	txt.move(-txt.getGlobalBounds().width / 2, 0);
}
