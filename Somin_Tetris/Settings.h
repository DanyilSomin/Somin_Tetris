#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <map>

#include "json.hpp"

const std::string settingsPath{ "settings.json" };

const std::string initPlayMode{ "Casual" };
const std::map<std::string, double> playModes  // Second value is acceleration of block speed per minute
{
	{"Casual", 0},
	{"Easy", 1 / 60},
	{"Normal", 2 /30},
	{"Hard", 3 / 60}
};

class Settings
{
public:
	static std::string getPlayMode();
	static std::string nextPlayMode();

	

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
