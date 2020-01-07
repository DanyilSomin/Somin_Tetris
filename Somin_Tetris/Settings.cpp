#include "Settings.h"

std::string Settings::getPlayMode()
{
	if (!get().m_json.contains("playmode"))
	{
		get().m_json["playMode"] = initPlayMode;
	}

	return get().m_json["playMode"];
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