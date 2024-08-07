#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
	float GetTime();
private:
	std::chrono::steady_clock::time_point last;
};
