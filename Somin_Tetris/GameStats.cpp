#include <algorithm>

#include "GameStats.h"

GameStats::GameStats()
	: startLevel{ Settings::getPlayDifficulty().first }
{
	read();
}

GameStats::~GameStats()
{
	save();
}

void GameStats::update(int linesCleared)
{
	if (linesCleared)
	{
		line += linesCleared;

		level = line / linesBeforeNextLevel + startLevel;

		nextDownTime = LEVEL_PERIODS[std::min(static_cast<int>(LEVEL_PERIODS.size() - 1), level)];

		if (linesCleared == TETRIS) 
		{ 
			tetrisLinesAmount += TETRIS; 
			tetrisRate = tetrisLinesAmount / static_cast<float>(line);
		}

		score += SCORE_POINTS_COEF[linesCleared] * (level + 1);
	}
}

void GameStats::save()
{
	Settings::setIfMaxLevel(level);
	Settings::setIfMaxLine(line);
	Settings::setIfMaxScore(score);
	Settings::setIfMaxTimeWithoutI(curMaxTimeWithoutI);
}

void GameStats::clear()
{
	line = 0;
	level = 0;
	tetrisRate = 0;
	tetrisLinesAmount = 0;
	score = 0;
	timeWithoutI = 0;
	curMaxTimeWithoutI = 0;
	linesBeforeNextLevel = 0;
}

void GameStats::read()
{
	level = startLevel;
	linesBeforeNextLevel = Settings::getPlayDifficulty().second;
	nextDownTime = LEVEL_PERIODS[std::min(static_cast<int>(LEVEL_PERIODS.size() - 1), level)];
	curMaxTimeWithoutI = Settings::getMaxTimeWithoutI();
}
