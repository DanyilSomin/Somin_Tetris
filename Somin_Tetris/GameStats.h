#pragma once

#include "Settings.h"
#include "TetrominosStates.h"

constexpr int TETRIS{ 4 };

class GameStats
{
public:
	GameStats();
	~GameStats();

	void update(int linesCleard);

	void save();

	void clear();

	void read();

	int getScore() const { return score; }

	int getLine() const { return line; }

	int getLevel() const { return level; }

	int getNextDownTime() const { return nextDownTime; }

	float getTetrisRate() const { return tetrisRate; }

	int getTimeWithoutI() const { return timeWithoutI; }
	void increaseTimeWithoutI() { curMaxTimeWithoutI = std::max(++timeWithoutI, curMaxTimeWithoutI); }
	void resetTimeWithoutI() { timeWithoutI = 0; }

private:
	int score{ 0 };

	int line{ 0 };

	int level{ 0 };

	int timeWithoutI{ 0 };

	int curMaxTimeWithoutI{ 0 };

	int nextDownTime{ 0 };	

	float tetrisRate{ 0 };

	int linesBeforeNextLevel{ 0 };

	int startLevel{ 0 };

	int tetrisLinesAmount{ 0 };
};