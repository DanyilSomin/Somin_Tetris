#include "MusicManager.h"

bool MusicManager::initialised = false;

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
}
