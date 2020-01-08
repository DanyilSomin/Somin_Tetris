#pragma once

#include <functional>
#include <thread>
#include <chrono>

class Timer
{
public:
	void stop() { running = false; }

	void run(float speed, const std::function<void()> &event);

	void addToSpeed(float deltaSpeed) 
	{ 
		if ((m_speed + deltaSpeed) > 0)
		{ 
			m_speed += deltaSpeed; 
		}
	}

private:
	float m_speed = 0;

	bool running = false;
};