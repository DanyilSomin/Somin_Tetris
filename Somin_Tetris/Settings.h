#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <utility>

#include "json.hpp"

const std::string settingsPath{ "settings.json" };

const std::string initPlayMode{ "Casual" };
const std::vector<std::pair<std::string, float>> playModes  
	// Second value is acceleration of block per second
{
	{"Casual", 0},
	{"Easy", 0.02 },
	{"Normal", 0.035 },
	{"Hard", 0.07}
};

class Settings
{
public:
	static const std::string getPlayMode();
	static const std::string nextPlayMode();

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
