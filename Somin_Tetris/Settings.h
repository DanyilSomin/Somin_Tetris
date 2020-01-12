#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <utility>

#include "json.hpp"

const std::string settingsPath{ "settings.json" };

const std::string initPlayMode{ "Casual" };

const std::vector<std::pair<std::string, std::pair<int, int>>> playModes
	// Difficulty - Starting level - Lines before new level
{
	{"Casual", {0 , 20} },
	{"Easy"  , {0 , 4} },
	{"Normal", {10, 6} },
	{"Hard"  , {20, 12} }
};

class Settings
{
public:
	static const std::string getPlayMode();
	static const std::string nextPlayMode();
	static const std::pair<int, int> getPlayDifficulty();

	Settings(const std::string &path);
	~Settings();

private:
	std::string m_path;

	nlohmann::json m_json;

	static Settings& get() 
	{ 
		static Settings m_settings{ settingsPath };
		return m_settings;
	}

	Settings(Settings const &) = delete;
	void operator=(Settings const &) = delete;
};
