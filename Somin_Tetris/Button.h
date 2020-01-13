#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <functional>

enum ButtonState
{
	NORMAL,
	HOWERED,
	CLICKED,
	BTN_STATES_COUNT,
};

const std::string SELECT_SOUND_PATH{ "Sound\\select.wav" };
const std::string CLICK_SOUND_PATH{ "Sound\\click.wav" };
const std::string FONT_PATH{ "Fonts\\Schlange_sans_bld.otf" };

class Button
{
public:
	Button(const sf::Vector2f &m_position, const std::string &text, 
		const std::function<void(void)> &onClickEvent = []() {});

	void setText(const std::string & txt);

	void draw(sf::RenderWindow &window);

	void setPosition(const sf::Vector2f &position);

	void move(const sf::Vector2f &delta);

	const sf::Text& getText() const { return m_texts[m_state]; }

	void setOnclickEvent(const std::function<void(void)> &ev) { m_onClickEvent = ev; }

	void click() { m_onClickEvent(); }

private:
	static bool lastUpdateMouseDown;

	int m_charSize{ 36 };

	std::string m_text;

	sf::Vector2f m_position;

	std::vector<sf::Text> m_texts;

	sf::SoundBuffer m_selectBuf;
	sf::SoundBuffer m_clickBuf;

	sf::Sound m_clickSound;
	sf::Sound m_selectSound;

	sf::Font m_font;

	std::function<void(void)> m_onClickEvent;

	ButtonState m_state = ButtonState::NORMAL;

	void defoultTextInit(sf::Text &txt);
	
	void update(sf::RenderWindow &window);
};

