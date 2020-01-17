#include "Button.h"

bool Button::lastUpdateMouseDown = false;

Button::Button(const sf::Vector2f &position, 
	const std::string &text, 
	const std::function<void(void)> &onClickEvent)
	: m_position{ position }, m_onClickEvent{ onClickEvent }, m_text{ text }
{
	m_font.loadFromFile(FONT_PATH);

	m_texts.resize(ButtonState::BTN_STATES_COUNT);
	for (auto &txt : m_texts)
	{
		defaultTextInit(txt);
	}

	m_texts[ButtonState::NORMAL].setFillColor(sf::Color::White);
	m_texts[ButtonState::HOWERED].setFillColor(sf::Color(200, 200, 200, 255));
	m_texts[ButtonState::CLICKED].setFillColor(sf::Color(160, 160, 160, 255));
}

void Button::setText(const std::string &text)
{
	m_text = text;

	for (auto &txt : m_texts)
	{
		txt.move(txt.getGlobalBounds().width / 2, 0);

		txt.setString(text);

		txt.move(-txt.getGlobalBounds().width / 2, 0);
	}
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(getText());
	update(window);
}

void Button::update(sf::RenderWindow &window)
{
	if (m_texts[m_state].getGlobalBounds().contains(
		static_cast<sf::Vector2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (!Button::lastUpdateMouseDown)
			{
				Button::lastUpdateMouseDown = true;
				MusicManager::playClick();
				m_state = ButtonState::CLICKED;
				m_onClickEvent();
			}
		}
		else if (m_state != ButtonState::HOWERED)
		{
			if (m_state == ButtonState::NORMAL)
			{
				MusicManager::playSelect();
			}

			m_state = ButtonState::HOWERED;

			Button::lastUpdateMouseDown = false;
		}
		else
		{
			lastUpdateMouseDown = false;
		}
	}
	else if (m_state == ButtonState::CLICKED)
	{
		m_state = ButtonState::HOWERED;
	}
	else
	{
		m_state = ButtonState::NORMAL;
	}
}

void Button::defaultTextInit(sf::Text &txt)
{
	txt.setCharacterSize(m_fontSize);
	txt.setFont(m_font);
	txt.setString(m_text);
	txt.setPosition(m_position);
	txt.setFillColor(sf::Color::White);
	txt.move(-txt.getGlobalBounds().width / 2, 0);
}

void Button::setPosition(const sf::Vector2f &m_position)
{
	for (auto &text : m_texts)
	{
		text.setPosition(m_position);
	}
}

void Button::move(const sf::Vector2f & delta)
{
	for (auto &text : m_texts)
	{
		text.move(delta);
	}
}
