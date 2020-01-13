#include "Settings.h"

const std::string Settings::getPlayMode()
{
	if (!get().m_json.contains("playMode"))
	{
		get().m_json["playMode"] = initPlayMode;
	}

	return get().m_json["playMode"];
}

const std::string Settings::nextPlayMode()
{
	auto it = std::find_if(playModes.begin(), playModes.end(), 
		[](const auto &el) { return el.first == getPlayMode(); });
	++it;

	std::string nextMode;

	if (it == playModes.end())
	{
		it = playModes.begin();
	}

	nextMode = it->first;

	get().m_json["playMode"] = nextMode;

	return nextMode;
}

const std::pair<int, int> Settings::getPlayDifficulty()
{
	auto it = std::find_if(playModes.begin(), playModes.end(),
		[](const auto &el) { return el.first == getPlayMode(); });

	if (it == playModes.end()) { return playModes.begin()->second; }
	else { return it->second; }
}

const std::string Settings::getMusicMode()
{
	if (!get().m_json.contains("musicMode"))
	{
		get().m_json["musicMode"] = initMusicMode;
	}

	return get().m_json["musicMode"];
}

const std::string Settings::muteMusic()
{
	get().m_json["musicMode"] = "Muted";
	return "Muted";
}

const std::string Settings::unmuteMusic()
{
	get().m_json["musicMode"] = "Unmuted";
	return "Unmuted";
}

const bool Settings::isMusicMuted()
{
	return getMusicMode() == "Muted";
}

Settings::Settings(const std::string &path)
	: m_path{ path }
{
	std::ifstream stream;
	stream.open(m_path);

	if (stream.is_open())
	{
		stream >> m_json;
	}

	stream.close();
}

Settings::~Settings()
{
	std::ofstream stream;
	stream.open(m_path, std::ofstream::trunc);

	if (stream.is_open())
	{
		stream << m_json;
	}

	stream.close();
}