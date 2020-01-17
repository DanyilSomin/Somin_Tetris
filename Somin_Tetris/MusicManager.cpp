#include "MusicManager.h"

MusicManager::MusicManager()
{
	music.openFromFile("Sound\\music.wav");
	music.setLoop(true);

	b_click.loadFromFile("Sound\\click.wav");
	b_levelUp.loadFromFile("Sound\\levelUp.wav");
	b_down.loadFromFile("Sound\\down.wav");
	b_drop.loadFromFile("Sound\\drop.wav");
	b_move.loadFromFile("Sound\\move.wav");
	b_pause.loadFromFile("Sound\\pause.wav");
	b_select.loadFromFile("Sound\\select.wav");
	b_gameOver.loadFromFile("Sound\\gameOver.wav");
	b_rotate.loadFromFile("Sound\\rotate.wav");
	b_tetris.loadFromFile("Sound\\tetris.wav");
	b_forbidden.loadFromFile("Sound\\forbidden.wav");

	click.setBuffer(b_click);
	select.setBuffer(b_select);
	levelUp.setBuffer(b_levelUp);
	down.setBuffer(b_down);
	drop.setBuffer(b_drop);
	move.setBuffer(b_move);
	pause.setBuffer(b_pause);
	select.setBuffer(b_select);
	gameOver.setBuffer(b_gameOver);
	rotate.setBuffer(b_rotate);
	tetris.setBuffer(b_tetris);
	forbidden.setBuffer(b_forbidden);
}

void MusicManager::updateMusicMode()
{
	if (Settings::isMusicMuted())
	{
		MusicManager::stopMusic();
	}
	else
	{
		MusicManager::playMusic();
	}

	get().isMuted = Settings::isSoundMuted();
}

void MusicManager::playClick() { if (!get().isMuted) get().click.play(); }
void MusicManager::playSelect() { if (!get().isMuted) get().select.play(); }
void MusicManager::playLevelUp() { if (!get().isMuted) get().levelUp.play(); }
void MusicManager::playDown() { if (!get().isMuted) get().down.play(); }
void MusicManager::playDrop() { if (!get().isMuted) get().drop.play(); }
void MusicManager::playMove() { if (!get().isMuted) get().move.play(); }
void MusicManager::playPause() { if (!get().isMuted) get().pause.play(); }
void MusicManager::playGameOver() { if (!get().isMuted) get().gameOver.play(); }
void MusicManager::playRotate() { if (!get().isMuted) get().rotate.play(); }
void MusicManager::playTetris() { if (!get().isMuted) get().tetris.play(); }
void MusicManager::playForbidden() { if (!get().isMuted) get().forbidden.play(); }
