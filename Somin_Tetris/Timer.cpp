#include "Timer.h"

void Timer::run(float speed, const std::function<void()> &event)
{
	running = true;

	std::thread th([=]() 
	{
		while (true) 
		{
			if (!running) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<size_t>(1000 / speed)));
			if (!running) return;
			event();
		}
	});

	th.detach();
}