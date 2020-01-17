#pragma once

#include <SFML\Audio.hpp>
#include "Settings.h"

class MusicManager
{
public:
	MusicManager();

	static void playClick();
	static void playSelect();
	static void playLevelUp();
	static void playDown();
	static void playDrop();
	static void playMove();
	static void playPause();
	static void playGameOver();
	static void playRotate();
	static void playTetris();
	static void playForbidden();

	static void playMusic() { if (!(get().music.getStatus() == sf::Sound::Playing)) get().music.play(); };
	static void stopMusic() { get().music.pause(); };

	static void updateMusicMode();

	static MusicManager& get()
	{
		static MusicManager m_musicManager{};
		return m_musicManager;
	}

	MusicManager(MusicManager const &) = delete;
	void operator=(MusicManager const &) = delete;

private:
	bool isMuted;

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
	sf::SoundBuffer b_tetris;
	sf::SoundBuffer b_forbidden;

	sf::Sound click;
	sf::Sound select;
	sf::Sound levelUp;
	sf::Sound down;
	sf::Sound drop;
	sf::Sound move;
	sf::Sound pause;
	sf::Sound gameOver;
	sf::Sound rotate;
	sf::Sound tetris;
	sf::Sound forbidden;
};
