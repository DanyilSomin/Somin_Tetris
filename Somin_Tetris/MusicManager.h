#pragma once

#include <SFML\Audio.hpp>

class MusicManager
{
public:
	MusicManager();

	static void playClick() { get().click.play(); }
	static void playSelect() { get().select.play(); }
	static void playLevelUp() { get().levelUp.play(); }
	static void playDown() { get().down.play(); }
	static void playDrop() { get().drop.play(); }
	static void playMove() { get().move.play(); }
	static void playPause() { get().pause.play(); }
	static void playGameOver() { get().gameOver.play(); }
	static void playRotate() { get().rotate.play(); }

	static void piayMusic() { get().music.play(); };
	static void stopMusic() { get().music.pause(); };

	static MusicManager& get()
	{
		static MusicManager m_musicManager{};
		return m_musicManager;
	}

	MusicManager(MusicManager const &) = delete;
	void operator=(MusicManager const &) = delete;

private:
	static bool initialised;

	sf::Music music;

	sf::SoundBuffer b_click;
	sf::SoundBuffer b_select;
	sf::SoundBuffer b_levelUp;
	sf::SoundBuffer b_down;
	sf::SoundBuffer b_drop;
	sf::SoundBuffer b_move;
	sf::SoundBuffer b_pause;
	sf::SoundBuffer b_gameOver;
	sf::SoundBuffer b_rotate;

	sf::Sound click;
	sf::Sound select;
	sf::Sound levelUp;
	sf::Sound down;
	sf::Sound drop;
	sf::Sound move;
	sf::Sound pause;
	sf::Sound gameOver;
	sf::Sound rotate;
};
