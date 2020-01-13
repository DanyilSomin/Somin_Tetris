#include "PopoutFrame.h"

PopoutFrame::PopoutFrame(const sf::Vector2f & position, const std::string & header)
	: m_position{ position }
{
	m_font.loadFromFile(FONT_PATH);

	m_rectangle.setFillColor(m_color);

	auto *txt{ new sf::Text };
	txt->setString(header);
	txt->setFont(m_font);
	txt->setFillColor(sf::Color::White);
	txt->setCharacterSize(HEADER_FONT_SIZE);
	txt->setPosition({ (m_position.x + BORDER_SIZE.x), (m_position.y + BORDER_SIZE.y) });
	m_texts.emplace_back(txt);

	alignCenter();
}

void PopoutFrame::draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);

	for (auto &text : m_texts)
	{
		window.draw(*text);
	}
	for (auto &btn : m_buttons)
	{
		btn->draw(window);
	}
}

void PopoutFrame::push(const std::string & str)
{
	auto *txt{ new sf::Text };
	txt->setString(str);
	txt->setFont(m_font);
	txt->setFillColor(sf::Color::White);
	txt->setCharacterSize(FONT_SIZE);

	float Y{ 0 };
	for (int i{ 1 }; i < m_texts.size(); ++i)
	{
		Y += m_texts[i]->getGlobalBounds().height + DISTANSE_BETWEEN;
	}
;
	Y += m_position.y;
	Y += BORDER_SIZE.y;
	Y += HEADER_FONT_SIZE;
	Y += DISTANSE_BETWEEN;

	txt->setPosition({ m_position.x + (m_size.x / 2), Y });
	txt->move(-txt->getGlobalBounds().width / 2, 0);

	m_texts.emplace_back(txt);

	for (auto &btn : m_buttons)
	{
		btn->move( { 0, txt->getGlobalBounds().height + DISTANSE_BETWEEN });
	}

	alignCenter();
}

void PopoutFrame::push(Button *btn)
{
	float Y{ 0 };
	for (int i{ 1 }; i < m_texts.size(); ++i)
	{
		Y += m_texts[i]->getGlobalBounds().height + DISTANSE_BETWEEN;
	}
	for (int i{ 0 }; i < m_buttons.size(); ++i)
	{
		Y += m_buttons[i]->getText().getGlobalBounds().height + DISTANSE_BETWEEN;
	}

	Y += m_position.y;
	Y += BORDER_SIZE.y;
	Y += HEADER_FONT_SIZE;
	Y += DISTANSE_BETWEEN;

	m_buttons.emplace_back(btn);
	m_buttons[m_buttons.size() - 1]->setPosition({ m_position.x + (m_size.x / 2), Y });

	alignCenter();
}

void PopoutFrame::push(const std::string &str, const std::function<void()>& onClick)
{
	float Y{ 0 };
	for (int i{ 1 }; i < m_texts.size(); ++i)
	{
		Y += m_texts[i]->getGlobalBounds().height + DISTANSE_BETWEEN;
	}
	for (int i{ 0 }; i < m_buttons.size(); ++i)
	{
		Y += m_buttons[i]->getText().getGlobalBounds().height + DISTANSE_BETWEEN;
	}
	
	Y += m_position.y;
	Y += BORDER_SIZE.y;
	Y += HEADER_FONT_SIZE;
	Y += DISTANSE_BETWEEN;

	m_buttons.emplace_back(new Button{ { m_position.x + (m_size.x / 2), Y }, str, onClick });
	m_buttons[m_buttons.size() - 1]->setPosition({ m_position.x + (m_size.x / 2), Y});
	
	alignCenter();
}

void PopoutFrame::resizeToFit()
{
	float maxX{ 0 };

	for (const auto &txt : m_texts)
	{
		maxX = std::max(maxX, txt->getLocalBounds().width);
	}
	for (const auto &btn : m_buttons)
	{
		maxX = std::max(maxX, btn->getText().getLocalBounds().width);
	}

	float Y{ 0 };

	for (const auto &txt : m_texts)
	{
		Y += txt->getLocalBounds().height + DISTANSE_BETWEEN;
	}

	for (const auto &btn : m_buttons)
	{
		Y += btn->getText().getLocalBounds().height + DISTANSE_BETWEEN;
	}

	//Y += m_buttons.size() * (FONT_SIZE + DISTANSE_BETWEEN);

	m_size = sf::Vector2f{ maxX, Y } +BORDER_SIZE + BORDER_SIZE;
}

void PopoutFrame::alignCenter()
{
	resizeToFit();

	m_rectangle.setPosition		                   
		(sf::Vector2f{ m_position.x - (m_size.x / 2), (*m_texts.begin())->getGlobalBounds().top - BORDER_SIZE.y });
		// m_position.y is not the same. 
		// We neds exactly the top coordinate of the header text.
		// It may hawe different values.

	m_rectangle.setSize(m_size);

	for (auto &txt : m_texts)
	{
		auto bounds{ txt->getGlobalBounds() };
		txt->setPosition({ m_position.x - (bounds.width / 2), txt->getPosition().y });
	}

	for (auto &button : m_buttons)
	{
		auto bounds{ button->getText().getGlobalBounds() };
		button->setPosition({ m_position.x - (bounds.width / 2), button->getText().getPosition().y });
	}
}

void PopoutFrame::update(sf::RenderWindow & window)
{
	for (auto &btn : m_buttons)
	{
		btn->draw(window);
	}

	draw(window);
}
