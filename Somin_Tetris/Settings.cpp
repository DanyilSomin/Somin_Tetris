#include "Settings.h"

const std::string Settings::getPlayMode()
{
	if (!get().m_json.contains("PlayMode"))
	{
		get().m_json["PlayMode"] = initPlayMode;
	}

	return get().m_json["PlayMode"];
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

	get().m_json["PlayMode"] = nextMode;

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
	if (!get().m_json.contains("MusicMode"))
	{
		get().m_json["MusicMode"] = initMusicMode;
	}

	if (get().m_json["MusicMode"] == "Muted")
	{
		return "Unmute music";
	}
	else
	{
		return "Mute music";
	}
}

const std::string Settings::muteMusic()
{
	get().m_json["MusicMode"] = "Muted";
	return "Unmute music";
}

const std::string Settings::unmuteMusic()
{
	get().m_json["MusicMode"] = "Unmuted";
	return "Mute music";
}

const bool Settings::isMusicMuted()
{
	return get().m_json["MusicMode"] == "Muted";
}

const std::string Settings::getSoundMode()
{
	if (!get().m_json.contains("SoundMode"))
	{
		get().m_json["SondMode"] = initSoundMode;
	}

	if (get().m_json["SoundMode"] == "Muted")
	{
		return "Unmute sounds";
	}
	else
	{
		return "Mute sound";
	}
}

const std::string Settings::muteSound()
{
	get().m_json["SoundMode"] = "Muted";
	return "Unmute sounds";
}

const std::string Settings::unmuteSound()
{
	get().m_json["SoundMode"] = "Unmuted";
	return "Mute sounds";
}

const bool Settings::isSoundMuted()
{
	return get().m_json["SoundMode"] == "Muted";
}

void Settings::setIfMaxScore(int score)
{
	if (get().m_json.contains("MaxScore"))
	{
		get().m_json["MaxScore"] = std::max(static_cast<int>(get().m_json["MaxScore"]), score);
	}
	else
	{
		get().m_json["MaxScore"] = score;
	}
}

int Settings::getMaxScore()
{
	if (get().m_json.contains("MaxScore"))
	{
		return get().m_json["MaxScore"];
	}
	return 0;
}

void Settings::setIfMaxLine(int line)
{
	if (get().m_json.contains("MaxLine"))
	{
		get().m_json["MaxLine"] = std::max(static_cast<int>(get().m_json["MaxLine"]), line);
	}
	else
	{
		get().m_json["MaxLine"] = line;
	}
}

int Settings::getMaxLine()
{
	if (get().m_json.contains("MaxLine"))
	{
		return get().m_json["MaxLine"];
	}
	return 0;
}

void Settings::setIfMaxLevel(int level)
{
	if (get().m_json.contains("MaxLevel"))
	{
		get().m_json["MaxLevel"] = std::max(static_cast<int>(get().m_json["MaxLevel"]), level);
	}
	else
	{
		get().m_json["MaxLevel"] = level;
	}
}

int Settings::getMaxLevel()
{
	if (get().m_json.contains("MaxLevel"))
	{
		return get().m_json["MaxLevel"];
	}
	return 0;
}

void Settings::setIfMaxTimeWithoutI(int timeWithoutI)
{
	if (get().m_json.contains("MaxTimeWithoutI"))
	{
		get().m_json["MaxTimeWithoutI"] = std::max(static_cast<int>(get().m_json["MaxTimeWithoutI"]), timeWithoutI);
	}
	else
	{
		get().m_json["MaxTimeWithiutI"] = timeWithoutI;
	}
}

int Settings::getMaxTimeWithoutI()
{
	if (get().m_json.contains("MaxTimeWithoutI"))
	{
		return get().m_json["MaxTimeWithoutI"];
	}
	else
	{
		get().m_json["MaxTimeWithoutI"] = 0;
	}
	return 0;
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